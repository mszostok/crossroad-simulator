#ifndef _VEHICLE_HPP_
#define _VEHICLE_HPP_

#include <string>
#include "TurnPattern.h"


using namespace std;


struct CrossVehicle{
	string _type;
	size_t _fromWhereToWhere;
};


/**
Klasa bazowa po której dziedzicz¹ wszystkie pojazdy które wystêpuj¹ na drodze tj. samochód, karetka i rower.
*/

class Vehicle{
public:
	/**
	Metody publiczne:
	tryToGo - wskaŸnik na jedn¹ z czterech funkcji (jazda w prawo, lewo, prost) przypisanych przez VehicleFactory pojazdów w trakcie tworzenia nowego obiektu.
	releaseLaneRoad - zwalnia zajmowane pasy które by³y zajête aby wkonaæ odpowiedni manwer.
	*/


	Vehicle(const Vehicle & vehToCpy);
	Vehicle(string name, TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time);
	virtual ~Vehicle();

	TurnPattern::pDirFunction tryToGo;
	void releaseLaneRoad(bool road[]);
	/**
	Zmienne publiczne:
	_type - nazwa pojazdu ( samochód, rower, karetka).
	_stop - liczba sekund na jak¹ zatrzymany zostaje pojazd kiedy musi ust¹piæ pierwszeñstwa pojazdowi uprzywilejowanemu.
	_dir  - kierunek jazdy pojazdu np. 32, czyli pojazd jedzie z drogi o id = 3 na drogê o id = 2, dziêki temu wiemy te¿ jaki to jest manwer. W tym przypadu bêdzie to skrêt w prawo.
	_timeToFinishCrossing - czas w jakim wykonuje dany manwer skrêtu w prawo, lewo lub jazdy prosto.
	*/
	string _type;
	size_t _stop,
		_dir,
		_timeToFinishCrossing;
};


class Car : public Vehicle {
public:
	Car(const Car & carToCpy);
	Car(TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time);
};


class Bike : public Vehicle{
	unsigned _timeToOvertaking; //czas po jakim rower bêdzie wyprzedza³ pojazdy przed sob¹
public:
	Bike(const Bike & bikeToCpy);
	Bike(TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time);
	bool tryToOvertaking(); // Metoda sprawdza czy rower powinen ju¿ wyprzedziæ pojazd bêd¹cy przed nim, za ka¿dym razem dekrementuje czas potrzebny do wyprzedzania.
	// Zwraca wartoœæ true - jeœli nale¿y wyprzedziæ, false - jeœli nie mo¿na jeszcze wyprzedzaæ
};


class Ambulance : public Vehicle{
public:
	Ambulance(const Ambulance & ambToCpy);
	Ambulance(TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time);
};
#endif