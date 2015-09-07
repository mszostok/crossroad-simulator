#include "GraphInterface.h"
#include "CrossroadSimulator.h"
#include "Crossroad.h"
#include "Vehicle.h"
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
GraphInterface::GraphInterface()
{

	drawCrossroads();
	printQueue();
	hideCursor();
}


GraphInterface::~GraphInterface(){}


/////////////////////


/**
Metody prywatne
*/

void GraphInterface::gotoxy(int x, int y){
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

};

void GraphInterface::printnSign(char sign, int n) {
	for (int i = 0; i <= n; i++)
		cout << sign;


}

void GraphInterface::drawCrossroads(){
	cout << "\t\t";
	printnSign('*', 45);

	cout << "\n\t\t\t Symulator skrzy¿owania \n\t drogi z pierwszeñstwem (N - S) z droga podporz¹dkowan¹ (E - W)" << endl;
	printnSign('*', 79);
	cout << "\t\t\t  \t|\t|\n  \t\t\t\t|   N   |\n  \t\t\t \t|\t|" << endl;
	cout << "\t\t\t  -------\t-------\n \t\t\t     W\t\t  E" << endl;
	cout << "\t\t\t  -------\t-------" << endl;
	cout << "\t\t\t  \t|\t|\n  \t\t\t\t|   S   |\n  \t\t\t\t|\t|" << endl;

}

void GraphInterface::printQueue(){

	cout << "\n\t\t\t Przejazdy samochodów" << endl << endl;
	cout << "Na drodze pó³nocnej :   0 \t | " << endl;
	cout << "Na drodze po³udniowej : 0 \t | " << endl;
	cout << "Na drodze wschodniej :  0 \t | " << endl;
	cout << "Na drodze zachodniej :  0 \t | " << endl << endl;
	cout << "Pojazdy doje¿d¿aj¹ce:    N: 0 | S: 0 | E: 0 | W: 0";
}

void GraphInterface::hideCursor(void){
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(hOut, &ConCurInf);

}

void GraphInterface::clrOncomingVehicle(){
	for (int x = 28; x < 50; x += 7){
		GraphInterface::gotoxy(x, 21);
		cout << "0";
	}
}

void GraphInterface::clrCrossingVehicle(){
	for (int y = 16; y < 20; ++y){
		GraphInterface::gotoxy(35, y);
		cout << " -------------------------------";
	}
}

void GraphInterface::displayCnt(size_t cnt){
	size_t offset = 0;
	if (cnt > 9) offset = 1;
	if (cnt > 99) offset = 2;

	gotoxy((36 - offset), 8);
	cout << cnt << "s  " << endl;


};

void GraphInterface::displayQueueVehicle(size_t where, size_t cnt){
	size_t offset = 0;
	size_t x = 24;
	switch (where){
	case PRIORITYN:
		GraphInterface::gotoxy(x, 16);
		break;
	case PRIORITYS:
		GraphInterface::gotoxy(x, 17);
		break;
	case SUBORDINATEE:
		GraphInterface::gotoxy(x, 18);
		break;
	case SUBORDINATEW:
		GraphInterface::gotoxy(x, 19);
		break;
	default:
		GraphInterface::gotoxy(0, 0);
		break;
	}
	cout << cnt << " ";
}

void GraphInterface::displayOncomingVehicle(size_t fromWhereToWhere){
	size_t fromWhere = fromWhereToWhere / 10;

	switch (fromWhere){
	case PRIORITYN:
		GraphInterface::gotoxy(28, 21);
		break;
	case PRIORITYS:
		GraphInterface::gotoxy(35, 21);
		break;
	case SUBORDINATEE:
		GraphInterface::gotoxy(42, 21);
		break;
	case SUBORDINATEW:
		GraphInterface::gotoxy(49, 21);
		break;
	default:
		GraphInterface::gotoxy(0, 0);
		break;
	}
	cout << "1";
}

void GraphInterface::displayCrossingVehicle(string type, size_t dir){
	size_t fromWhere = dir / 10;
	size_t toWhere = dir % 10;
	size_t x = 35;

	switch (fromWhere)
	{
	case 1:
		GraphInterface::gotoxy(x, 16);
		if (toWhere == 2) cout << "\" " << type << " \" skrêci³ w lewo.          " << endl;
		if (toWhere == 3) cout << "\" " << type << " \" przejecha³ prosto.       " << endl;
		if (toWhere == 4) cout << "\" " << type << " \" skrêci³ w prawo.         " << endl;
		break;
	case 2:
		GraphInterface::gotoxy(x, 18);
		if (toWhere == 3) cout << "\" " << type << " \" skrêci³ w lewo.          " << endl;
		if (toWhere == 4) cout << "\" " << type << " \" przejecha³ prosto.       " << endl;
		if (toWhere == 1) cout << "\" " << type << " \" skrêci³ w prawo.         " << endl;
		break;
	case 3:
		GraphInterface::gotoxy(x, 17);
		if (toWhere == 4) cout << "\" " << type << " \" skrêci³ w lewo.          " << endl;
		if (toWhere == 1) cout << "\" " << type << " \" przejecha³ prosto.       " << endl;
		if (toWhere == 2) cout << "\" " << type << " \" skrêci³ w prawo.         " << endl;
		break;
	case 4:
		GraphInterface::gotoxy(x, 19);
		if (toWhere == 1) cout << "\" " << type << " \" skrêci³ w lewo.          " << endl;
		if (toWhere == 2) cout << "\" " << type << " \" przejecha³ prosto.       " << endl;
		if (toWhere == 3) cout << "\" " << type << " \" skrêci³ w prawo.         " << endl;
		break;
	default:
		break;
	}

};

/////////////////////

/**
Metody publiczne
*/


ostream & operator << (ostream &output, const CrossroadInformation &data){

	GraphInterface::displayCnt(data._cntSimulation);
	GraphInterface::clrOncomingVehicle();
	GraphInterface::clrCrossingVehicle();

	for (list<CrossVehicle>::const_iterator it = data._crossingVehicle.begin(); it != data._crossingVehicle.end(); ++it){
		GraphInterface::displayCrossingVehicle(it->_type, it->_fromWhereToWhere);
	}

	for (list<OncomingVehicle>::const_iterator it = data._oncomingVehicle.begin(); it != data._oncomingVehicle.end(); ++it){
		GraphInterface::displayOncomingVehicle(it->_fromWhereToWhere);
	}

	for (multimap<string, QueueOnLaneRoad>::const_iterator it = data._queuesOnCrossroad.begin(); it != data._queuesOnCrossroad.end(); ++it){
		GraphInterface::displayQueueVehicle(it->second._id, it->second._cnt);
	}


	return output;
}

void GraphInterface::display(const CrossroadInformation & data){ cout << data << endl; }

////////////