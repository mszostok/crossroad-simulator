#ifndef _CROSSROAD_HPP_
#define _CROSSROAD_HPP_

#define ROADCNT 4
#define PRIORITYN 1
#define PRIORITYS 3
#define SUBORDINATEE 2 
#define SUBORDINATEW 4
#include <string>
#include <fstream> 
#include <vector>
#include <iostream>
#include <list>
#include <map>
#include "Vehicle.h"

#include "ProbabilityPattern.h"

using namespace std;

/**
Na podstawie tej klasy mo�na stworzy� obiekt przedsawiaj�cy kolejki na danym pasie ruchu.
_cnt - Liczba samochodow w kolejce.
_id  - Indentyfikator drogi.
_queueEmergencyVehicle - lista pojazd�w uprzwilejowanych
_queueVehicle - lista wska�nik�w na obiekty klasy bazowej Vehicle i jej pochodnych
_pToQueuueBikes - lista wska�nikow na obiekty klasy Bike kt�re przechowywane s� na li�cie _queueVehicle  (u�atwia ich zamian� przy wyprzedzaniu)
*/

class QueueOnLaneRoad
{
public:
	QueueOnLaneRoad(int);
	~QueueOnLaneRoad();

	int _id;
	size_t _cnt;

	list< Ambulance> _queueEmergencyVehicle;
	list< Vehicle *> _queueVehicle;
	list< Bike *> _pToQueueBikes;
};



/**
Na podstawie tej klasy mo�na stworzy� obiekt przedstawiaj�cy skrzy�owanie drogi g��wnej z podporz�dkowan�.
_queueOnCrossroad  - przedstawia kolejki na drogach na skrzy�owaniu (N- p�nocna, S - po�udnie, E - wsch�d, W - zach�d).
Ponadto multimapa jest sortuj�cym kontenerem asocjacyjnym wi�c ju� uzyskamy porz�dek tj. priority przed subordinate.
_crossingVeh       - lista pojazd�w przejed�aj�cych przez skrzy�owanie.
_standardRoad      - tablica przedstawiaj�ca czy dany pas ruchu na drodze jest zaj�ty (True - zaj�ty, Flase - wolny).
Zasad "zaj�to�ci pasa ruchu"  przestrzegaj� tylko pojazdy nieuprzywilejowane
_emergencyRoad     - tablica przedstawiaj�ca czy dany pas ruchu na drodze jest zaj�ty (True - zaj�ty, Flase - wolny).
Zasad "zaj�to�ci pasa ruchu" przestrzegaj� zar�wno pojazdy uprzywilejowane i nieuprzywilejowane.
*/

class Crossroad
{
	/**
	Zaprzyja�nienie ze wzgl�du na funkcj� kopiuj�c� informacje odno�nie samochod�w na skorzy�owaniu
	*/
	friend class CrossroadSimulator;

	/**
	Klasa wyj�tk�w
	*/
	class CrossroadException{
		string _exceptionName;

	public:
		CrossroadException(string name) : _exceptionName(name){};
		string what() const;
	};
	/**
	Alias multimapy
	*/
	typedef multimap<string, QueueOnLaneRoad> _queueOnRoad;

	_queueOnRoad _queuesOnCrossroad;
	list<Vehicle> _crossingVeh;
	bool _standardRoad[ROADCNT];
	bool _emergencyRoad[ROADCNT];

public:
	/**
	Aliasy multimapy i iterator�w list
	*/
	typedef multimap<string, QueueOnLaneRoad> _queueOnRoad;
	typedef list<Ambulance>::iterator _itAmbulance;
	typedef list<Vehicle *>::iterator _itVeh;

	Crossroad();
	~Crossroad();

	/**
	Metody publiczne:
	insert -  dwukrotnie przeci��ona metoda kt�ra pozwala na umieszczenie samochodu, karetki lub roweru w odpowiedniej kolejce na skrzy�owaniu.
	Argumenty wywo�ania to kolejno obiekt przedstawiaj�cy dany pojazd, kierunek jazdy.
	checkEmergencyVehicle -  sprawdza czy jaki� uprzywilejowany pojazd b�d�cy w kolejce nie powinien przejecha�.
	checkStandardVehicle  -  sprawdza czy pojazdy (za wyj�tkiem uprzywilejowanych) nie powinny przejecha� przez skrzy�owanie.
	stopTraffic           -  zatrzymuje wszystkie pojazdy wykonuj�ce przejazdy przez skrzy�owanie je�li maj� ust�pi� miejsc� pojazd� uprzywilejowanym.
	addToCrossingVeh      -  przeci��ona metoda kt�ra pozwala doda� pojazdy do odpowiednich list pojazd�w przeje�d�aj�cych przez skrzy�owanie.
	Argumenty wywo�ania: obiekt kt�ry jest pojazdem uprzywilejowanym (wtedy zostanie dodanych to listy pojazd�w przeje�d�aj�cych ale uprzywilejowanych)
	lub obiekt kt�ry jest zwyk�ym pojazdem (zostanie dodany do listy zwyk�ych pojazd�w wykonuj�cych przejazdy przez skrzy�owanie) oraz dla obu przypadk�w
	nale�y r�wnie� poda� list� z kt�rej pochodzi pojazd aby mo�lwie by�o jego zwolnienie.
	checkCrossingVehicle  -  sprawdza pojazdy przeje�d�aj�ce przez skrzy�owanie. Je�li uko�czy�y manwer to je zwalania je�eli nie to dekrementuje im czas potrzebny na przejazd.
	checkTraffic		  -  sprawdza ruch na skrzy�owaniu wywo�uj�c kolejno checkEmergencyVehicle, checkStandardVehicle oraz checkCrossingVehicle;
	*/
	void insert(Car &, size_t);
	void insert(Ambulance &, size_t);
	void insert(Bike &, size_t);

	void checkEmergencyVehicle();
	void checkStandardVehicle();
	void stopTraffic(size_t);

	_itAmbulance & addToCrossingVeh(_itAmbulance & itAmbulance, QueueOnLaneRoad&);
	_itVeh & addToCrossingVeh(_itVeh & itVeh, QueueOnLaneRoad&);

	list<CrossVehicle> checkTraffic();
	list<CrossVehicle> checkCrossingVehicle();





};

#endif


