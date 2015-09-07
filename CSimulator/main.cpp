#include <iostream>
#include "CrossroadSimulator.h"
#include "GraphInterface.h"
#include <locale>

/**
Wykrywanie wycieków
*/
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)


using namespace std;


void mainFunction(int & argc, char **argv){

	setlocale(LC_ALL, "polish"); //ustawienie wyœwietlania polskich znaków w konsoli

	bool stop = false;
	size_t delay = 1000;
	time_t Tend, Tstart;

	CrossroadSimulator simulator01(argc, argv);
	GraphInterface GUI;

	while (!stop){
		Tstart = clock();

		simulator01.simulate();
		GUI.display(simulator01.getData());

		Tend = clock();
		while ((Tend - Tstart) < delay) {
			if (GetAsyncKeyState(VK_ESCAPE)){
				stop = true;
				break;
			};
			Tend = clock();
		};
	};
}

int main(int argc, char **argv){
	/** Umieszczenie w osobnej funkcji cia³a funkcji main, u³atwia wykrywanie wycieków pamiêci,
	poniewa¿ po opuszczeniu tego bloku wszystkie zmienne powinny byæ zwolnione.
	*/
	system("cls");
	mainFunction(argc, argv);

	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}