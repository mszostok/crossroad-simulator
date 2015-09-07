#ifndef _VEHICLEFACTORY_HPP_
#define _VEHICLEFACTORY_HPP_
#include <map>
#include <string>
#include "Vehicle.h"
#include "TurnPattern.h"
#include <map>

using namespace std;

/**
Klasa kt�rej obiekty s� fabrykami pojazd�w.
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
	returnCar - zwraca samocho�d. Arg wywo�ania kierunek w kt�rym jedzie samoch�d.
	Nast�pne analogicznie.
	*/

	Car returnCar(size_t);
	Bike returnBike(size_t);
	Ambulance returnAmbulance(size_t);
};


#endif
