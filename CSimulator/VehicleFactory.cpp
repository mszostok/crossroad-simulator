#include "VehicleFactory.h"
/**
Wykrywanie wycieków
*/
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)



/**
Konstruktor & destruktor
*/
VehicleFactory::VehicleFactory(){}
VehicleFactory::~VehicleFactory(){}

/////////////////////

/**
Metody prywatne
*/


/////////////////////////////


/**
Metody publiczne
*/

Car VehicleFactory::returnCar(size_t dir){
	TurnPattern::TurnPatternData tmp = turnPattern.returnPattern(dir, "car");
	Car vehicle(tmp._pTurnFunction, dir, tmp._time);

	return vehicle;

};

Bike VehicleFactory::returnBike(size_t dir){
	TurnPattern::TurnPatternData tmp = turnPattern.returnPattern(dir, "bike");
	Bike vehicle(tmp._pTurnFunction, dir, tmp._time);

	return vehicle;

};

Ambulance VehicleFactory::returnAmbulance(size_t dir){
	TurnPattern::TurnPatternData tmp = turnPattern.returnPattern(dir, "ambulance");
	Ambulance vehicle(tmp._pTurnFunction, dir, tmp._time);

	return vehicle;

};
////////////