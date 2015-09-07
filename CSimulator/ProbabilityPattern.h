#ifndef _PROBABILITYPATTERN_HPP_
#define _PROBABILITYPATTERN_HPP_
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

/**
Klasa kt�rej obiekty przechowuj� informacje odno�nie prawdopdobie�stw wczytanych z pliku.
_probRoad - mapa kt�ra przechowuje informacje nt. prawdopodobie�stw wyst�pienia pojazdu na danej drodze, kluczem jest droga, warto�ci� prawdopodobie�stwo.
_probVehicle - mapa kt�ra przechowuje informacje nt. prawdopodobie�stwa wyst�pienia danego typu, kluczem jest nazwa pojazdu, warto�ci� prawdopodobie�stwo.
*/

class UserProbPattern{

	map<size_t, size_t> _probRoad;
	map<string, size_t> _probVehicle;

public:
	/**
	Aliasy iterator�w poszczeg�lnych map
	*/
	typedef map<size_t, size_t>::const_iterator iteratorRoad;
	typedef map<string, size_t>::const_iterator iteratorVehicle;

	UserProbPattern(const UserProbPattern &);
	UserProbPattern(vector<string>); //parser, wczytanie do _probPattern 
	~UserProbPattern();
	/**
	Gettery
	*/
	size_t size(string) const;
	iteratorRoad beginRoad() const;
	iteratorVehicle beginVehicle() const;
	iteratorRoad endRoad() const;
	iteratorVehicle endVehicle() const;
};

/**
Klasa kt�rej obiekty przechowuj� informacje odno�nie prawdopdobie�stw wykonania okre�lonego manweru.
_probSubordinate - prawdopodobie�stwa wykonaia okre�lonego manweru b�d�c na drodze podporz�dkowanej. Kluczem jest nazwa pojazdu, warto�ci� prawdopodobie�stwo.
_probPriority    - prawdopodobie�stwa wykonaia okre�lonego manweru b�d�c na drodze g��wnej. Kluczem jest nazwa pojazdu, warto�ci� prawdopodobie�stwo.
*/

class TurnProbPattern{
	map<string, size_t> _probSubordinate;
	map<string, size_t> _probPriority;

public:
	/**
	Alias iteratora map'y
	*/
	typedef std::map<string, size_t>::const_iterator iterator;

	TurnProbPattern();

	/**
	Gettery
	*/
	iterator begin(size_t) const;
	iterator end(size_t) const;


};
#endif

