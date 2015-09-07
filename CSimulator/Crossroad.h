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
Na podstawie tej klasy mo¿na stworzyæ obiekt przedsawiaj¹cy kolejki na danym pasie ruchu.
_cnt - Liczba samochodow w kolejce.
_id  - Indentyfikator drogi.
_queueEmergencyVehicle - lista pojazdów uprzwilejowanych
_queueVehicle - lista wskaŸników na obiekty klasy bazowej Vehicle i jej pochodnych
_pToQueuueBikes - lista wskaŸnikow na obiekty klasy Bike które przechowywane s¹ na liœcie _queueVehicle  (u³atwia ich zamianê przy wyprzedzaniu)
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
Na podstawie tej klasy mo¿na stworzyæ obiekt przedstawiaj¹cy skrzy¿owanie drogi g³ównej z podporz¹dkowan¹.
_queueOnCrossroad  - przedstawia kolejki na drogach na skrzy¿owaniu (N- pó³nocna, S - po³udnie, E - wschód, W - zachód).
Ponadto multimapa jest sortuj¹cym kontenerem asocjacyjnym wiêc ju¿ uzyskamy porz¹dek tj. priority przed subordinate.
_crossingVeh       - lista pojazdów przejed¿aj¹cych przez skrzy¿owanie.
_standardRoad      - tablica przedstawiaj¹ca czy dany pas ruchu na drodze jest zajêty (True - zajêty, Flase - wolny).
Zasad "zajêtoœci pasa ruchu"  przestrzegaj¹ tylko pojazdy nieuprzywilejowane
_emergencyRoad     - tablica przedstawiaj¹ca czy dany pas ruchu na drodze jest zajêty (True - zajêty, Flase - wolny).
Zasad "zajêtoœci pasa ruchu" przestrzegaj¹ zarówno pojazdy uprzywilejowane i nieuprzywilejowane.
*/

class Crossroad
{
	/**
	ZaprzyjaŸnienie ze wzglêdu na funkcjê kopiuj¹c¹ informacje odnoœnie samochodów na skorzy¿owaniu
	*/
	friend class CrossroadSimulator;

	/**
	Klasa wyj¹tków
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
	Aliasy multimapy i iteratorów list
	*/
	typedef multimap<string, QueueOnLaneRoad> _queueOnRoad;
	typedef list<Ambulance>::iterator _itAmbulance;
	typedef list<Vehicle *>::iterator _itVeh;

	Crossroad();
	~Crossroad();

	/**
	Metody publiczne:
	insert -  dwukrotnie przeci¹¿ona metoda która pozwala na umieszczenie samochodu, karetki lub roweru w odpowiedniej kolejce na skrzy¿owaniu.
	Argumenty wywo³ania to kolejno obiekt przedstawiaj¹cy dany pojazd, kierunek jazdy.
	checkEmergencyVehicle -  sprawdza czy jakiœ uprzywilejowany pojazd bêd¹cy w kolejce nie powinien przejechaæ.
	checkStandardVehicle  -  sprawdza czy pojazdy (za wyj¹tkiem uprzywilejowanych) nie powinny przejechaæ przez skrzy¿owanie.
	stopTraffic           -  zatrzymuje wszystkie pojazdy wykonuj¹ce przejazdy przez skrzy¿owanie jeœli maj¹ ust¹piæ miejscê pojazd¹ uprzywilejowanym.
	addToCrossingVeh      -  przeci¹¿ona metoda która pozwala dodaæ pojazdy do odpowiednich list pojazdów przeje¿d¿aj¹cych przez skrzy¿owanie.
	Argumenty wywo³ania: obiekt który jest pojazdem uprzywilejowanym (wtedy zostanie dodanych to listy pojazdów przeje¿d¿aj¹cych ale uprzywilejowanych)
	lub obiekt który jest zwyk³ym pojazdem (zostanie dodany do listy zwyk³ych pojazdów wykonuj¹cych przejazdy przez skrzy¿owanie) oraz dla obu przypadków
	nale¿y równie¿ podaæ listê z której pochodzi pojazd aby mo¿lwie by³o jego zwolnienie.
	checkCrossingVehicle  -  sprawdza pojazdy przeje¿d¿aj¹ce przez skrzy¿owanie. Jeœli ukoñczy³y manwer to je zwalania je¿eli nie to dekrementuje im czas potrzebny na przejazd.
	checkTraffic		  -  sprawdza ruch na skrzy¿owaniu wywo³uj¹c kolejno checkEmergencyVehicle, checkStandardVehicle oraz checkCrossingVehicle;
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


