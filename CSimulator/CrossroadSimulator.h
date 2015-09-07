#ifndef _CROSSROADSIMULATOR_HPP_
#define _CROSSROADSIMULATOR_HPP_
#include <string>
#include <algorithm>
#include <iostream>
#include <time.h> // dla srand
#include <windows.h> // dla simulate
#include "VehicleFactory.h"
#include "Crossroad.h"
#include "ProbabilityPattern.h"


using namespace std;

/**
Struktura w kt�rej przechowywane s� informacje odno�nie samochodu kt�ry nadjed�a do skrzy�owania.
*/
struct OncomingVehicle {
	string _type;
	size_t _fromWhereToWhere;
}; //wystarczy domyslny konstruktor

/**
Struktura w kt�rej przechowywane s� informacje na temat niekt�rych dzia�a� sumalatora.
_cntSimulation - licznik symulacji,
_oncomingVehicle - lista nadjed�aj�cych samochod�w,
_crossingVehicle - lista samochod�w kt�re przejecha�y przez skrzy�owanie //niestety myl�ca jest nazwa w tym przypadku
_queuesOnCrossroad - jest to kopia kolejek powstaj�cych na skrzy�owaniu
*/
struct CrossroadInformation{
	size_t _cntSimulation;
	list< OncomingVehicle > _oncomingVehicle;
	list< CrossVehicle > _crossingVehicle;
	multimap<string, QueueOnLaneRoad> _queuesOnCrossroad;
}; //wystarczy domyslny konstruktor


/**
Na podstawie klasy CrossroadSimulator mo�na stworzy� obiekt kt�ry b�dzie symulatorem skrzy�owania drogi g�ownej z drog� podporz�dkowan�.
Zmienne prywatne:
_data        - przechowuje informacje na temat niekt�rych dzia�a� symulatora. Informacje kt�re mo�na uzyska� wymienione s� wy�ej.
_filename    - przechowuje nazw� pliku podanego przez u�ytkownika w kt�rym znajduj� si� prawdopodobie�stwa wyst�pienia samochodu na drodze i jego typu.
_crossroad   - obiekt klasy Crossroad jest obiektem przedstawiaj�cym skrzy�owanie dr�g podporz�dkowanej i g��wnej.
Sama klasa szerzej zosta�a opisana w pliku Crossroad.h
_pUserProb   - jest to wska�nik na obiekt klasy UserProbPattern przechowuj�cy prawdopodobie�stwa zadane przez u�ytkownika.
Sama klasa szerzej zosta�a opisana w pliku ProbabilityPattern.h
_probToTurn  - jest to obiekt klasy TurnProbPattern przechowuj�cy prawdopodobie�stwo jazdy pojazdu w okre�lonym kierunku.
_vehicleType - przechowuje tym aktualnie wylosowanego pojazdu
_vehicleDir  - przechowuje kierunek aktualnie wylosowanego pojazdu
_factory     - obiekt klasy VehicleFactory kt�ry jest fabryk� pojazd�w, innymi s�owy, zwraca pojazdy o wskazanym typie i kierunku jazdy.
Sama klasa szerzej zosta�a opisana w pliku VehicleFactory.h
*/

class CrossroadSimulator
{
	/**
	Klasa wyjatk�w
	*/
	class CrossroadException{
		string _exceptionName;
	public:
		CrossroadException(string);
		string what() const;
	};

	CrossroadInformation _data;
	string _filename;
	Crossroad _crossroad;
	UserProbPattern * _pUserProb;
	TurnProbPattern _probToTurn;
	string _vehicleType;
	size_t _vehicleDir;
	VehicleFactory _factory;

	/**
	Metody prywatne:
	getCmdOption - pobiera nazw� pliku z arg wywo�ania programu. Argumenty metody to kolejno argc, argv oraz nazwa flagi np. "-c". Zwraca nazw� kt�ra wyst�pi�a po okre�lonej fladze.
	LoadUserProb - tworzy obiekt klasy UserProbPattern z prawdopodobie�stwami odczytanymi z pliku. Arg metody jest nazwa pliku z danymi. Zwraca obiekt utworzony obiekt.\
	Random       - losuje liczb� z przedzia�u 0-100. Zwraca wylosowan� liczb�.
	setVehicleApperance   - sprawdza czy na drodze powinien pojawi� si� pojazd zgodnie zadanym wcze�niej prawdopodobie�stwem. Je�li tak to pojazd jest dodawany do listy nadje�d�aj�cych pojazd�w.
	addVehicleToCrossroad - dodaje pojazdy z listy nadjed�aj�cych do odpowiednich kolejek na skrzy�owaniu.
	setVehicleType        - losuje typ pojazdu zgodznie zadanym prawdopodobie�stwem. Zwraca wylosowany typ.
	setVehicleDir         - losuje kierunek pojazdu  zgodznie zadanym prawdopodobie�stwem. Zwraca wylosowany kierunek.
	*/
	string getCmdOption(char ** begin, char ** end, const string & option) const;
	UserProbPattern LoadUserProb(string &);
	size_t Random() const;

	void setVehicleApperance();
	void addVehicleToCrossroad();
	string setVehicleType();
	int setVehicleDir(size_t);

public:
	/**
	Alias iteratora map'y
	*/
	typedef map<size_t, map<string, size_t>>::const_iterator itOncomingVeh;

	CrossroadSimulator(int &, char **);
	~CrossroadSimulator();
	/**
	Metody publiczne:
	simulate - wywo�uje kolejno addVehicleToCrossroad(), setVehicleApperance() i sprawdza ruch na skrzy�owaniu (_crossroad.checkTraffic())
	getData  - zwraca informacje na temat niekt�rych dzia�a� symulatora. Informacje kt�re mo�na uzysk�� wymienione przy opisie klasy CrossroadInformation.
	*/
	void simulate();
	CrossroadInformation & getData();
};

#endif

