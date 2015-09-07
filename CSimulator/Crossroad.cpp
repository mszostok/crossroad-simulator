#include "Crossroad.h"
#include <algorithm>
#include <list>
#include <functional>
#include <iterator>
/**
Wykrywanie wycieków
*/
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

/**
Konstruktor & destruktor CrossroadExcepiton
*/
string Crossroad::CrossroadException::what() const{
	return _exceptionName;
}
/////////////

/**
Konstruktor & destruktor
*/

Crossroad::Crossroad()
{


	_queuesOnCrossroad.insert(make_pair("priorityN", QueueOnLaneRoad(1)));
	_queuesOnCrossroad.insert(make_pair("priorityS", QueueOnLaneRoad(3)));
	_queuesOnCrossroad.insert(make_pair("subordinateE", QueueOnLaneRoad(2)));
	_queuesOnCrossroad.insert(make_pair("subordinateW", QueueOnLaneRoad(4)));

	/*nale¿y byæ czujnym przy wprowadzaniu kolejnych dróg, poniewa¿ id jest zarówno indeksem
	jak i numerem drogi potrzebnym do okreœlania czy droga jest po prawej czy po lewej,
	jeœli jest po prawej to ma id mniejsze o jeden jeœli po lewej to ma id wieksze o 1 */

	for (int i = 0; i < ROADCNT; ++i) { _emergencyRoad[i] = _standardRoad[i] = false; }

}


Crossroad::~Crossroad()
{
	cout << "destrukcja Crossroad" << endl;
}


/////////////////////

/**
Konstruktor & destruktor QueueOnLaneRoad
*/


QueueOnLaneRoad::QueueOnLaneRoad(int id) : _id(id), _cnt(0){}

QueueOnLaneRoad::~QueueOnLaneRoad(){

	_queueEmergencyVehicle.clear();
	_queueVehicle.clear();
	_pToQueueBikes.clear();

}
///////////////////



/**
Metody prywatne
*/


/////////////////////

/**
Metody publiczne
*/


void Crossroad::insert(Car & vehicle1, size_t road){
	Car *vehicle = new Car(vehicle1);
	for (_queueOnRoad::iterator it = _queuesOnCrossroad.begin(); it != _queuesOnCrossroad.end(); ++it){
		if (it->second._id == road){
			it->second._queueVehicle.push_back(vehicle);
			++(it->second._cnt);
		}
	}
};

void Crossroad::insert(Ambulance & vehicle1, size_t road){
	Ambulance vehicle(vehicle1);
	for (_queueOnRoad::iterator it = _queuesOnCrossroad.begin(); it != _queuesOnCrossroad.end(); ++it){
		if (it->second._id == road){
			it->second._queueEmergencyVehicle.push_back(vehicle);
			++(it->second._cnt);
		}
	}
};

void Crossroad::insert(Bike & vehicle1, size_t road){
	Bike *vehicle = new Bike(vehicle1);
	for (_queueOnRoad::iterator it = _queuesOnCrossroad.begin(); it != _queuesOnCrossroad.end(); ++it){
		if (it->second._id == road){
			it->second._queueVehicle.push_back(vehicle);
			it->second._pToQueueBikes.push_back(dynamic_cast< Bike *>(it->second._queueVehicle.back()));
			++(it->second._cnt);
		}
	}
};

void Crossroad::checkEmergencyVehicle(){
	for (_queueOnRoad::iterator it = _queuesOnCrossroad.begin(); it != _queuesOnCrossroad.end(); ++it){
		for (_itAmbulance itAmbulance = it->second._queueEmergencyVehicle.begin(); itAmbulance != it->second._queueEmergencyVehicle.end();){
			if (itAmbulance->tryToGo(_emergencyRoad, itAmbulance->_dir)){ //mo¿e jechaæ tzn. nie blokuje jej ¿aden inny pojazd uprzywilejowany

				stopTraffic(itAmbulance->_timeToFinishCrossing);
				itAmbulance = addToCrossingVeh(itAmbulance, it->second); // return it->second._queueEmergencyVehicle.erase(itAmbulance);
			}
			else{
				itAmbulance++;
			}
		}
	}
}

void Crossroad::checkStandardVehicle(){

	for (_queueOnRoad::iterator it = _queuesOnCrossroad.begin(); it != _queuesOnCrossroad.end(); ++it){

		for (_itVeh itVeh = it->second._queueVehicle.begin(); itVeh != it->second._queueVehicle.end();){

			if (next(itVeh) != it->second._queueVehicle.end()){
				if ((**(next(itVeh)))._type == "bike"){
					Bike * bikeTMP = dynamic_cast<Bike *>(*(next(itVeh)));
					if (bikeTMP){ // NULL - nie uda³o siê rzutowanie
						if (bikeTMP->tryToOvertaking()){
							std::swap(**itVeh, (**(next(itVeh))));
						}
					}
				}
			}
			if ((**itVeh).tryToGo(_standardRoad, (**itVeh)._dir)){ //mo¿e jechaæ tzn. nie blokuje jej ¿aden inny pojazd 

				itVeh = addToCrossingVeh(itVeh, it->second); // return it->second._queueVehicle.erase(itVeh);
			}
			else { itVeh++; }
		}
	}
}

Crossroad::_itAmbulance & Crossroad::addToCrossingVeh(Crossroad::_itAmbulance & itAmbulance, QueueOnLaneRoad& queue){

	Ambulance ambulance(*itAmbulance);
	_crossingVeh.push_back(ambulance);
	itAmbulance = queue._queueEmergencyVehicle.erase(itAmbulance);
	--queue._cnt;
	return itAmbulance;
}

Crossroad::_itVeh & Crossroad::addToCrossingVeh(Crossroad::_itVeh & itVeh, QueueOnLaneRoad& queue){

	Vehicle veh(**itVeh);

	_crossingVeh.push_back(veh);
	itVeh = queue._queueVehicle.erase(itVeh);
	--queue._cnt;
	return itVeh;
}

list<CrossVehicle> Crossroad::checkCrossingVehicle(){
	list<CrossVehicle> tmpList;
	for (list<Vehicle>::iterator it = _crossingVeh.begin(); it != _crossingVeh.end();){
		if (it->_stop <= 0) { --(it->_timeToFinishCrossing); }
		else { --(it->_stop); };

		if (it->_timeToFinishCrossing <= 0){
			CrossVehicle tmpElem;
			tmpElem._fromWhereToWhere = it->_dir;
			tmpElem._type = it->_type;
			tmpList.push_back(tmpElem);
			it->releaseLaneRoad(_standardRoad);
			it = _crossingVeh.erase(it);
		}
		else { ++it; }
	}
	return tmpList;
}

void Crossroad::stopTraffic(size_t delay){

	for (list<Vehicle>::iterator it = _crossingVeh.begin(); it != _crossingVeh.end(); ++it){
		if (!it->tryToGo(_emergencyRoad, it->_dir))
			it->_stop = delay;
	}

}

list<CrossVehicle> Crossroad::checkTraffic(){

	checkEmergencyVehicle();
	checkStandardVehicle();

	return checkCrossingVehicle();

}


//////////////////////////////////


