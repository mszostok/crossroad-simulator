#ifndef _TURNPATTERN_HPP_
#define _TURNPATTERN_HPP_
#include <string>
#include <iostream>
using namespace std;

/**
Klasa której obiekty przedstawiaj¹ wszystkie mo¿liwe funkcje manewrów i ich czasy.
Przez odpowiedni¹ metodê zwracaj¹ do nich wskaŸniki i wartoœci.
*/

class TurnPattern
{
public:
	/*
	Alias na typ wskaŸnika na funkcjê.
	*/
	typedef bool(*pDirFunction)(bool road[], size_t dir);
	/**
	Struktura która przechowuje informacje zwracane przez metodê tej klasy
	_pTurnFunction - wskaŸnik na jedn¹ z metod odpowiedzialn¹ za wykonanie manweru
	_time - czasu okreœlonego manewru
	*/
	struct TurnPatternData{
		pDirFunction _pTurnFunction;
		size_t _time;
	};

	TurnPattern();
	~TurnPattern();

	/**
	Metody publiczne: (statyczne) - dostêpne nawet gdy nie istnieje obiekt tej klasy
	firstCondition - sprawdza czy dany pojazd mo¿e przejechaæ. Arg wywo³ania tablica przedstawiaj¹ca czy dany pas ruchu na drodze jest zajêty, kierunek pojazdu.
	prirityTryLeft - sprawdza czy pojazd mo¿e jechaæ w danym kierunku. Wszystkie nastêpne metody analogicznie.
	returnPattern  - zwraca strukturê w/w. Arg wywo³ania kierunek i typ pojazdu.

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