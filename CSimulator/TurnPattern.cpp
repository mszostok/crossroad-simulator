#include "TurnPattern.h"
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
TurnPattern::TurnPattern(){}

TurnPattern::~TurnPattern(){}

/////////////////////

/**
Metody prywatne
*/
bool TurnPattern::firstCondition(bool road[], size_t dir){
	size_t fromWhere = dir / 10;
	size_t toWhere = dir % 10;
	toWhere -= 1;
	if (toWhere < 0) toWhere = 3;
	for (size_t i = fromWhere - 1; i != toWhere;){
		if (road[i])
			return false;
		--i;
		if (i < 0) i = 3;
	}
	for (size_t i = fromWhere - 1; i != toWhere;){
		road[i] = true;
		--i;
		if (i < 0) i = 3;
	}
	return true;
};

bool TurnPattern::secondCondition(size_t dir){

	return 1;
};

/////////////////////////////


/**
Metody publiczne
*/
bool TurnPattern::priorityTryStraight(bool road[], size_t dir){

	return TurnPattern::firstCondition(road, dir);
};

bool TurnPattern::priorityTryLeft(bool road[], size_t dir){

	return TurnPattern::firstCondition(road, dir);
};

bool TurnPattern::priorityTryRight(bool road[], size_t dir){

	return TurnPattern::firstCondition(road, dir);
};

bool TurnPattern::subordinateTryStraight(bool road[], size_t dir){

	return TurnPattern::firstCondition(road, dir);
};

bool TurnPattern::subordinateTryLeft(bool road[], size_t dir){

	return TurnPattern::firstCondition(road, dir);
};

bool TurnPattern::subordinateTryRight(bool road[], size_t dir){

	return TurnPattern::firstCondition(road, dir);
};

TurnPattern::TurnPatternData TurnPattern::returnPattern(size_t dir, string type){

	TurnPattern::TurnPatternData tmp;

	switch (dir)
	{
	case 13:
	case 31:
		tmp._pTurnFunction = priorityTryStraight;
		if (type == "car"){ tmp._time = 1; }
		else if (type == "bike"){ tmp._time = 2; }
		else if (type == "ambulance"){ tmp._time = 1; }

		return tmp;
		break;
	case 42:
	case 24:
		tmp._pTurnFunction = subordinateTryStraight;
		if (type == "car"){ tmp._time = 1; }
		else if (type == "bike"){ tmp._time = 2; }
		else if (type == "ambulance"){ tmp._time = 1; }

		return tmp;
		break;
	case 32:
	case 14:
		tmp._pTurnFunction = priorityTryRight;
		if (type == "ambulance"){ tmp._time = 4; }
		else if (type == "car"){ tmp._time = 2; }
		else if (type == "bike"){ tmp._time = 3; }

		return tmp;
		break;
	case 21:
	case 43:
		tmp._pTurnFunction = subordinateTryRight;
		if (type == "ambulance"){ tmp._time = 4; }
		else if (type == "car"){ tmp._time = 2; }
		else if (type == "bike"){ tmp._time = 3; }

		return tmp;
		break;
	case 12:
	case 34:
		tmp._pTurnFunction = priorityTryLeft;
		if (type == "ambulance"){ tmp._time = 5; }
		else if (type == "car"){ tmp._time = 3; }
		else if (type == "bike"){ tmp._time = 5; }

		return tmp;
		break;
	case 23:
	case 41:
		tmp._pTurnFunction = subordinateTryLeft;
		if (type == "ambulance"){ tmp._time = 5; }
		else if (type == "car"){ tmp._time = 3; }
		else if (type == "bike"){ tmp._time = 5; }

		return tmp;
		break;
	default:
		tmp._pTurnFunction = NULL;
		tmp._time = 0;
		return tmp;
		break;
	};
};

/////////////
