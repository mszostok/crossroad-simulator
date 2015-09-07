#include "ProbabilityPattern.h"
#include "Crossroad.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

/**
Konstruktor & destruktor
*/

UserProbPattern::UserProbPattern(const UserProbPattern &copyPattern)
{
	_probVehicle = copyPattern._probVehicle;
	_probRoad = copyPattern._probRoad;
}

UserProbPattern::UserProbPattern(vector <string> textToParse) {
	try{
		size_t found;
		for (vector<string>::iterator it = textToParse.begin(); it != textToParse.end(); ++it){
			if (it->compare("") == 0){
				continue;
			}
			if (it->at(0) == '/')
				continue;

			if ((found = it->find("priority=")) != string::npos){
				it->erase(0, found + 9);
				int value = stoi((*it));

				_probRoad.insert(make_pair(PRIORITYN, value));
				_probRoad.insert(make_pair(PRIORITYS, value));

				continue;
			}

			if ((found = it->find("subordinate=")) != string::npos){
				it->erase(0, found + 12);
				int value = stoi((*it));

				_probRoad.insert(make_pair(SUBORDINATEE, value));
				_probRoad.insert(make_pair(SUBORDINATEW, value));
				continue;
			}



			if ((found = it->find("ambulance=")) != string::npos){
				it->erase(0, found + 10);
				int value = stoi((*it));

				_probVehicle.insert(make_pair("ambulance", value));
				continue;
			}

			if ((found = it->find("car=")) != string::npos){
				it->erase(0, found + 4);
				int value = stoi((*it));

				_probVehicle.insert(make_pair("car", value));
				continue;
			}


		};
	}
	catch (std::invalid_argument &e){
		std::cerr << e.what() << endl;
		exit(3);
	}
	catch (...){
		std::cerr << "B³ad wczytania wartoœci prawdopodobieñstw. SprawdŸ czy plik jest poprawnie sformatowany." << endl;
		exit(3);
	}

}

UserProbPattern::~UserProbPattern()
{
	//cout << "destrukcja UserProbPattern" << endl;

}

//////////////////////

/**
Metody publiczne
*/

size_t UserProbPattern::size(string type) const {
	transform(type.begin(), type.end(), type.begin(), ::tolower);
	if (type == "road")
		return _probRoad.size();

	else if (type == "vehicle")
		return _probVehicle.size();

	return 0;

}

UserProbPattern::iteratorRoad UserProbPattern::beginRoad() const { return _probRoad.begin(); }

UserProbPattern::iteratorVehicle UserProbPattern::beginVehicle() const { return _probVehicle.begin(); }

UserProbPattern::iteratorRoad UserProbPattern::endRoad() const { return _probRoad.end(); }

UserProbPattern::iteratorVehicle UserProbPattern::endVehicle() const { return _probVehicle.end(); }

//////////////////



/**
Konstruktor & destruktor
*/

/**
Wzorzec prawdopodobieñstwa skrêtów uwarunkowanych type drogi (podporz¹dkowana, g³ówna)
*/

TurnProbPattern::TurnProbPattern(){

	_probPriority.insert(make_pair("straight", 90));
	_probPriority.insert(make_pair("right", 5));
	_probPriority.insert(make_pair("left", 5));

	_probSubordinate.insert(make_pair("straight", 34));
	_probSubordinate.insert(make_pair("left", 33));
	_probSubordinate.insert(make_pair("right", 33));

}
///////////////////

/**
Metody publiczne
*/
TurnProbPattern::iterator TurnProbPattern::begin(size_t type) const {
	if (type == PRIORITYN || type == PRIORITYS)
		return _probPriority.begin();
	else
		return _probSubordinate.begin();

}

TurnProbPattern::iterator TurnProbPattern::end(size_t type) const {
	if (type == PRIORITYN || type == PRIORITYS)
		return _probPriority.end();
	else
		return _probSubordinate.end();

}

//////////////////