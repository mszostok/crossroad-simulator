#ifndef _TURNPATTERN_HPP_
#define _TURNPATTERN_HPP_
#include <string>
#include <iostream>
using namespace std;

/**
Klasa kt�rej obiekty przedstawiaj� wszystkie mo�liwe funkcje manewr�w i ich czasy.
Przez odpowiedni� metod� zwracaj� do nich wska�niki i warto�ci.
*/

class TurnPattern
{
public:
	/*
	Alias na typ wska�nika na funkcj�.
	*/
	typedef bool(*pDirFunction)(bool road[], size_t dir);
	/**
	Struktura kt�ra przechowuje informacje zwracane przez metod� tej klasy
	_pTurnFunction - wska�nik na jedn� z metod odpowiedzialn� za wykonanie manweru
	_time - czasu okre�lonego manewru
	*/
	struct TurnPatternData{
		pDirFunction _pTurnFunction;
		size_t _time;
	};

	TurnPattern();
	~TurnPattern();

	/**
	Metody publiczne: (statyczne) - dost�pne nawet gdy nie istnieje obiekt tej klasy
	firstCondition - sprawdza czy dany pojazd mo�e przejecha�. Arg wywo�ania tablica przedstawiaj�ca czy dany pas ruchu na drodze jest zaj�ty, kierunek pojazdu.
	prirityTryLeft - sprawdza czy pojazd mo�e jecha� w danym kierunku. Wszystkie nast�pne metody analogicznie.
	returnPattern  - zwraca struktur� w/w. Arg wywo�ania kierunek i typ pojazdu.

	*/
	static bool firstCondition(bool road[], size_t dir);
	static bool secondCondition(size_t dir);

	//priority
	static bool priorityTryLeft(bool road[], size_t dir);
	static bool priorityTryRight(bool road[], size_t dir);
	static bool priorityTryStraight(bool road[], size_t dir);
	//subordinate
	static bool subordinateTryLeft(bool road[], size_t dir);
	static bool subordinateTryRight(bool road[], size_t dir);
	static bool subordinateTryStraight(bool road[], size_t dir);

	TurnPatternData returnPattern(size_t, string);
};

#endif