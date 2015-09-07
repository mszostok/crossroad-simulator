#ifndef _GRAPINTERFACE_HPP_
#define _GRAPHINTERFACE_HPP__
#include <Windows.h>
#include "CrossroadSimulator.h"
#include <map>

/**
Obiekt tej klasy jest interfejsem graficznym u�ytkownika.
Metody prywatne:
printnSign - wy�wietla znak o zadanej "d�ugo�ci". Arg wywo�ania: znak typu char, liczba jego powt�rze�.
drawCrossroads - wy�wietla schemat skrzy�owania.
printQueue - wy�wietla stany poszczeg�lnych kolejek.
gotoxy - ustawia kursor na zadanej pozycji. Arg wywo�ania: pozycja na osi x, pozycja na osi y.
clrOncomingVehicle - czy�ci kolejki nadje�d�aj�cych pojazd�w wy�wietlanych w konsoli.
clrCrossingVehicle - czy�ci kolejki przeje�d�aj�cych pojazd�w wy�wietlanych w konsoli.
displayOncomingVehicle - wy�wietla kolejki nadje�d�aj�cych pojazd�w.
displayQueueVehicles   - wy�wietla kolejki pojazd�w b�d�cych na skrzy�owaniu.
displayCnt  - wy�wietla liczb� symulacji.
displayCrossingVehicle - wy�wietla pojazdy kt�re przejecha�y przez skrzy�owanie //myl�ca nazwa

hideCursor - ukrywa kursor w oknie konsoli.
*/

class GraphInterface
{

	static void printnSign(char sign, int n);
	static void drawCrossroads();
	static void printQueue();
	static void gotoxy(int x, int y);
	static void clrOncomingVehicle();
	static void clrCrossingVehicle();
	static void displayOncomingVehicle(size_t);
	static void displayQueueVehicle(size_t, size_t);
	static void displayCnt(size_t cnt);
	static void displayCrossingVehicle(string, size_t);

	void hideCursor(void);
public:

	GraphInterface();
	~GraphInterface();

	/**
	Metody publiczne:
	display - wy�wietla informacje odno�nie stanu symulacji.

	ponadto zosta� zaprzyja�niony operator wy�wietlania w celu �atwiejszego wy�wietlania informacji.
	*/
	friend ostream & operator << (ostream &output, const CrossroadInformation &data);
	void display(const CrossroadInformation & data);
};


#endif