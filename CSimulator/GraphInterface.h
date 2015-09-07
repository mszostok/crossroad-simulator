#ifndef _GRAPINTERFACE_HPP_
#define _GRAPHINTERFACE_HPP__
#include <Windows.h>
#include "CrossroadSimulator.h"
#include <map>

/**
Obiekt tej klasy jest interfejsem graficznym u¿ytkownika.
Metody prywatne:
printnSign - wyœwietla znak o zadanej "d³ugoœci". Arg wywo³ania: znak typu char, liczba jego powtórzeñ.
drawCrossroads - wyœwietla schemat skrzy¿owania.
printQueue - wyœwietla stany poszczególnych kolejek.
gotoxy - ustawia kursor na zadanej pozycji. Arg wywo³ania: pozycja na osi x, pozycja na osi y.
clrOncomingVehicle - czyœci kolejki nadje¿d¿aj¹cych pojazdów wyœwietlanych w konsoli.
clrCrossingVehicle - czyœci kolejki przeje¿d¿aj¹cych pojazdów wyœwietlanych w konsoli.
displayOncomingVehicle - wyœwietla kolejki nadje¿d¿aj¹cych pojazdów.
displayQueueVehicles   - wyœwietla kolejki pojazdów bêd¹cych na skrzy¿owaniu.
displayCnt  - wyœwietla liczbê symulacji.
displayCrossingVehicle - wyœwietla pojazdy które przejecha³y przez skrzy¿owanie //myl¹ca nazwa

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
	display - wyœwietla informacje odnoœnie stanu symulacji.

	ponadto zosta³ zaprzyjaŸniony operator wyœwietlania w celu ³atwiejszego wyœwietlania informacji.
	*/
	friend ostream & operator << (ostream &output, const CrossroadInformation &data);
	void display(const CrossroadInformation & data);
};


#endif