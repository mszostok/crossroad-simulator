#ifndef _PROBABILITYPATTERN_HPP_
#define _PROBABILITYPATTERN_HPP_
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

/**
Klasa której obiekty przechowuj¹ informacje odnoœnie prawdopdobieñstw wczytanych z pliku.
_probRoad - mapa która przechowuje informacje nt. prawdopodobieñstw wyst¹pienia pojazdu na danej drodze, kluczem jest droga, wartoœci¹ prawdopodobieñstwo.
_probVehicle - mapa która przechowuje informacje nt. prawdopodobieñstwa wyst¹pienia danego typu, kluczem jest nazwa pojazdu, wartoœci¹ prawdopodobieñstwo.
*/

class UserProbPattern{

	map<size_t, size_t> _probRoad;
	map<string, size_t> _probVehicle;

public:
	/**
	Aliasy iteratorów poszczególnych map
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
Klasa której obiekty przechowuj¹ informacje odnoœnie prawdopdobieñstw wykonania okreœlonego manweru.
_probSubordinate - prawdopodobieñstwa wykonaia okreœlonego manweru bêd¹c na drodze podporz¹dkowanej. Kluczem jest nazwa pojazdu, wartoœci¹ prawdopodobieñstwo.
_probPriority    - prawdopodobieñstwa wykonaia okreœlonego manweru bêd¹c na drodze g³ównej. Kluczem jest nazwa pojazdu, wartoœci¹ prawdopodobieñstwo.
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

