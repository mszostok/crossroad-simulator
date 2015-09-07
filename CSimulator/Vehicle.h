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
Klasa bazowa po kt�rej dziedzicz� wszystkie pojazdy kt�re wyst�puj� na drodze tj. samoch�d, karetka i rower.
*/

class Vehicle{
public:
	/**
	Metody publiczne:
	tryToGo - wska�nik na jedn� z czterech funkcji (jazda w prawo, lewo, prost) przypisanych przez VehicleFactory pojazd�w w trakcie tworzenia nowego obiektu.
	releaseLaneRoad - zwalnia zajmowane pasy kt�re by�y zaj�te aby wkona� odpowiedni manwer.
	*/


	Vehicle(const Vehicle & vehToCpy);
	Vehicle(string name, TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time);
	virtual ~Vehicle();

	TurnPattern::pDirFunction tryToGo;
	void releaseLaneRoad(bool road[]);
	/**
	Zmienne publiczne:
	_type - nazwa pojazdu ( samoch�d, rower, karetka).
	_stop - liczba sekund na jak� zatrzymany zostaje pojazd kiedy musi ust�pi� pierwsze�stwa pojazdowi uprzywilejowanemu.
	_dir  - kierunek jazdy pojazdu np. 32, czyli pojazd jedzie z drogi o id = 3 na drog� o id = 2, dzi�ki temu wiemy te� jaki to jest manwer. W tym przypadu b�dzie to skr�t w prawo.
	_timeToFinishCrossing - czas w jakim wykonuje dany manwer skr�tu w prawo, lewo lub jazdy prosto.
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
	unsigned _timeToOvertaking; //czas po jakim rower b�dzie wyprzedza� pojazdy przed sob�
public:
	Bike(const Bike & bikeToCpy);
	Bike(TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time);
	bool tryToOvertaking(); // Metoda sprawdza czy rower powinen ju� wyprzedzi� pojazd b�d�cy przed nim, za ka�dym razem dekrementuje czas potrzebny do wyprzedzania.
	// Zwraca warto�� true - je�li nale�y wyprzedzi�, false - je�li nie mo�na jeszcze wyprzedza�
};


class Ambulance : public Vehicle{
public:
	Ambulance(const Ambulance & ambToCpy);
	Ambulance(TurnPattern::pDirFunction pTurnFunction, size_t dir, size_t time);
};
#endif