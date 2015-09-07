#include "Vehicle.h"

/**
Wykrywanie wycieków
*/
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

/** VEHICLE */
/**
Konstruktor & destruktor
*/
Vehicle::Vehicle(string name, TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time) : _type(name), tryToGo(pTurnFunction), _stop(0), _dir(dir), _timeToFinishCrossing(time){};

Vehicle::Vehicle(const Vehicle & vehToCpy) : _type(vehToCpy._type), tryToGo(vehToCpy.tryToGo), _stop(0), _dir(vehToCpy._dir), _timeToFinishCrossing(vehToCpy._timeToFinishCrossing){};

Vehicle::~Vehicle(){};
///////////

/**
Metody publiczne
*/

void Vehicle::releaseLaneRoad(bool road[]){

	size_t fromWhere = _dir / 10;
	size_t toWhere = _dir % 10;
	toWhere -= 1;
	if (toWhere < 0) toWhere = 3;
	for (size_t i = fromWhere - 1; i != toWhere;){
		road[i] = false;
		--i;
		if (i < 0) i = 3;
	}

}

///////////////////////////

/** AMBULANCE */
/**
Konstruktor
*/

Ambulance::Ambulance(const Ambulance & ambToCpy) : Vehicle(ambToCpy._type, ambToCpy.tryToGo, ambToCpy._dir, ambToCpy._timeToFinishCrossing){};

Ambulance::Ambulance(TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time) : Vehicle("ambulance", pTurnFunction, dir, time) {};

///////////////////////////

/** CAR */
/**
Konstruktor	CAR
*/
Car::Car(const Car & carToCpy) : Vehicle(carToCpy._type, carToCpy.tryToGo, carToCpy._dir, carToCpy._timeToFinishCrossing){};

Car::Car(TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time) : Vehicle("car", pTurnFunction, dir, time) {};

/////////////////////////////

/**BIKE */
/**
Konstruktor
*/
Bike::Bike(const Bike & bikeToCpy) : Vehicle(bikeToCpy._type, bikeToCpy.tryToGo, bikeToCpy._dir, bikeToCpy._timeToFinishCrossing), _timeToOvertaking(5){};
Bike::Bike(TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time) : Vehicle("bike", pTurnFunction, dir, time), _timeToOvertaking(5) {};

/**
Metody prywatne
*/
bool Bike::tryToOvertaking(){
	--_timeToOvertaking;
	if (_timeToOvertaking <= 0){
		_timeToOvertaking = 5;
		return true;
	}
	else
		return false;
};

/////////////////////