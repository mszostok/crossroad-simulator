#ifndef _VEHICLEFACTORY_HPP_
#define _VEHICLEFACTORY_HPP_
#include <map>
#include <string>
#include "Vehicle.h"
#include "TurnPattern.h"
#include <map>

using namespace std;

/**
Klasa której obiekty s¹ fabrykami pojazdów.
turnPattern - obiekt klasy TurnPattern. Szerzej opisana w pliku TurnPattern.h
*/

class VehicleFactory
{
	TurnPattern turnPattern;
public:
	VehicleFactory();
	~VehicleFactory();

	/**
	Metody publiczne:
	returnCar - zwraca samochoód. Arg wywo³ania kierunek w którym jedzie samochód.
	Nastêpne analogicznie.
	*/

	Car returnCar(size_t);
	Bike returnBike(size_t);
	Ambulance returnAmbulance(size_t);
};


#endif
