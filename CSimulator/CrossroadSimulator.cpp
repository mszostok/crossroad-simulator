#include "CrossroadSimulator.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

/**
Konstruktor & destruktor CrossroadExcepiton
Przy tworzeniu obiektu konstrukor potrzebuje nazwy wyj¹tku który wystapi³.
*/
CrossroadSimulator::CrossroadException::CrossroadException(string exceptionName) : _exceptionName(exceptionName){};

string CrossroadSimulator::CrossroadException::what() const {
	return _exceptionName;
};
///////////


/**
Konstruktor & destruktor
*/
CrossroadSimulator::CrossroadSimulator(int &argc, char **argv) {
	try {
		/*Na podstawie
		"The value of argv[argc] shall be 0" (C++03 §3.6.1/2), argv cannot be null. */
		_filename = getCmdOption(argv, argv + argc, "-c");
		_pUserProb = new UserProbPattern(LoadUserProb(_filename));

	}
	catch (CrossroadException &e){
		cerr << e.what();
		system("pause");
		exit(1);
	};

	srand(static_cast<int>(time(NULL)));


}

CrossroadSimulator::~CrossroadSimulator()
{
	cout << "destrukcja CrossroadSimulator" << endl;
	delete _pUserProb;
}

/////////////////////



/**
Metody prywatne
*/
string CrossroadSimulator::getCmdOption(char ** begin, char ** end, const std::string & option) const
{
	char ** itr = find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}

	throw CrossroadException("Brak poprawnych argumentów lini polecen\n");
}

UserProbPattern CrossroadSimulator::LoadUserProb(string  &filename){

	ifstream file;
	file.open(filename, std::ios::in);
	if (!file.is_open())
		throw CrossroadException("B³¹d odczytu pliku");

	vector < string > textToParse;
	string buff;

	while (getline(file, buff)) {
		textToParse.push_back(buff);
	}
	file.close();

	UserProbPattern setPattern(textToParse);

	return setPattern;
}

size_t  CrossroadSimulator::Random() const {

	return rand() % 101;
}

void CrossroadSimulator::setVehicleApperance(){ //zdarzenia niezalezne
	size_t rand = 0;

	for (UserProbPattern::iteratorRoad it = _pUserProb->beginRoad(); it != _pUserProb->endRoad(); ++it){
		rand = Random();
		if (rand <= (it->second)) {
			OncomingVehicle tmp{ setVehicleType(), setVehicleDir(it->first) };

			_data._oncomingVehicle.push_back(tmp);//it->first to id 0 - N, 1 - E, 2 - S, 3 -W
		}

	};

};

string CrossroadSimulator::setVehicleType(){
	size_t rand = Random();
	size_t last = 0;

	for (UserProbPattern::iteratorVehicle it = _pUserProb->beginVehicle(); it != _pUserProb->endVehicle(); ++it){
		if ((last <= rand) && (rand < (last += it->second))) // sprawdzamy, czy wylosowana liczba mieœci siê w zakresie p-stwa
			return it->first;
	};
	return "bike"; //jeœli suma prawdopodobieñstw pojawienia siê samochodu i ambulansu nie daje 100 to wtedy "wylosowany" zostaje rower 

};

int CrossroadSimulator::setVehicleDir(size_t road){
	size_t rand = Random();
	size_t secondRoad = road;
	size_t last = 0;
	size_t direction = NULL;
	for (TurnProbPattern::iterator it = _probToTurn.begin(road); it != _probToTurn.end(road); ++it){
		if ((last <= rand) && (rand <= (last += it->second))){ // sprawdzamy, czy wylosowana liczba mieœci siê w zakresie p-stwa
			direction = 10 * road;
			if (it->first == "straight"){
				if ((secondRoad += 2) > 4) secondRoad = secondRoad % 4; // 2 - która droga od lewej  4 - ile dróg na skrzy¿owaniu
				break;
			}
			if (it->first == "right"){
				if ((--secondRoad) <= 0) secondRoad += 4; //max id czyli dodac tyle ile jest dróg
				break;
			}
			if (it->first == "left"){
				if ((++secondRoad) > 4) secondRoad = PRIORITYN; //min id
				break;
			}
		}
	};
	direction += secondRoad;
	return direction;

}

void CrossroadSimulator::addVehicleToCrossroad(){
	for (list<OncomingVehicle>::iterator it = _data._oncomingVehicle.begin(); it != _data._oncomingVehicle.end(); ++it){
		size_t fromWhere = (it->_fromWhereToWhere) / 10;
		if (it->_type == "car") _crossroad.insert(_factory.returnCar(it->_fromWhereToWhere), fromWhere);

		else if (it->_type == "bike") _crossroad.insert(_factory.returnBike(it->_fromWhereToWhere), fromWhere);

		else _crossroad.insert(_factory.returnAmbulance(it->_fromWhereToWhere), fromWhere);
	}
	_data._oncomingVehicle.clear(); // zwolnienie dodanych pojazdów
}


/////////////////////////////


/**
Metody publiczne
*/

void CrossroadSimulator::simulate(){
	++(_data._cntSimulation);
	addVehicleToCrossroad();
	setVehicleApperance();
	_data._crossingVehicle = _crossroad.checkTraffic();
}

CrossroadInformation & CrossroadSimulator::getData(){
	_data._queuesOnCrossroad = _crossroad._queuesOnCrossroad;
	return _data;
};

/////////////

