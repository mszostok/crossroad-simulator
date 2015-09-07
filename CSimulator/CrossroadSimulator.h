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
Struktura w której przechowywane s¹ informacje odnoœnie samochodu który nadjed¿a do skrzy¿owania.
*/
struct OncomingVehicle {
	string _type;
	size_t _fromWhereToWhere;
}; //wystarczy domyslny konstruktor

/**
Struktura w której przechowywane s¹ informacje na temat niektórych dzia³añ sumalatora.
_cntSimulation - licznik symulacji,
_oncomingVehicle - lista nadjed¿aj¹cych samochodów,
_crossingVehicle - lista samochodów które przejecha³y przez skrzy¿owanie //niestety myl¹ca jest nazwa w tym przypadku
_queuesOnCrossroad - jest to kopia kolejek powstaj¹cych na skrzy¿owaniu
*/
struct CrossroadInformation{
	size_t _cntSimulation;
	list< OncomingVehicle > _oncomingVehicle;
	list< CrossVehicle > _crossingVehicle;
	multimap<string, QueueOnLaneRoad> _queuesOnCrossroad;
}; //wystarczy domyslny konstruktor


/**
Na podstawie klasy CrossroadSimulator mo¿na stworzyæ obiekt który bêdzie symulatorem skrzy¿owania drogi g³ownej z drog¹ podporz¹dkowan¹.
Zmienne prywatne:
_data        - przechowuje informacje na temat niektórych dzia³añ symulatora. Informacje które mo¿na uzyskaæ wymienione s¹ wy¿ej.
_filename    - przechowuje nazwê pliku podanego przez u¿ytkownika w którym znajduj¹ siê prawdopodobieñstwa wyst¹pienia samochodu na drodze i jego typu.
_crossroad   - obiekt klasy Crossroad jest obiektem przedstawiaj¹cym skrzy¿owanie dróg podporz¹dkowanej i g³ównej.
Sama klasa szerzej zosta³a opisana w pliku Crossroad.h
_pUserProb   - jest to wskaŸnik na obiekt klasy UserProbPattern przechowuj¹cy prawdopodobieñstwa zadane przez u¿ytkownika.
Sama klasa szerzej zosta³a opisana w pliku ProbabilityPattern.h
_probToTurn  - jest to obiekt klasy TurnProbPattern przechowuj¹cy prawdopodobieñstwo jazdy pojazdu w okreœlonym kierunku.
_vehicleType - przechowuje tym aktualnie wylosowanego pojazdu
_vehicleDir  - przechowuje kierunek aktualnie wylosowanego pojazdu
_factory     - obiekt klasy VehicleFactory który jest fabryk¹ pojazdów, innymi s³owy, zwraca pojazdy o wskazanym typie i kierunku jazdy.
Sama klasa szerzej zosta³a opisana w pliku VehicleFactory.h
*/

class CrossroadSimulator
{
	/**
	Klasa wyjatków
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
	getCmdOption - pobiera nazwê pliku z arg wywo³ania programu. Argumenty metody to kolejno argc, argv oraz nazwa flagi np. "-c". Zwraca nazwê która wyst¹pi³a po okreœlonej fladze.
	LoadUserProb - tworzy obiekt klasy UserProbPattern z prawdopodobieñstwami odczytanymi z pliku. Arg metody jest nazwa pliku z danymi. Zwraca obiekt utworzony obiekt.\
	Random       - losuje liczbê z przedzia³u 0-100. Zwraca wylosowan¹ liczbê.
	setVehicleApperance   - sprawdza czy na drodze powinien pojawiæ siê pojazd zgodnie zadanym wczeœniej prawdopodobieñstwem. Jeœli tak to pojazd jest dodawany do listy nadje¿d¿aj¹cych pojazdów.
	addVehicleToCrossroad - dodaje pojazdy z listy nadjed¿aj¹cych do odpowiednich kolejek na skrzy¿owaniu.
	setVehicleType        - losuje typ pojazdu zgodznie zadanym prawdopodobieñstwem. Zwraca wylosowany typ.
	setVehicleDir         - losuje kierunek pojazdu  zgodznie zadanym prawdopodobieñstwem. Zwraca wylosowany kierunek.
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
	simulate - wywo³uje kolejno addVehicleToCrossroad(), setVehicleApperance() i sprawdza ruch na skrzy¿owaniu (_crossroad.checkTraffic())
	getData  - zwraca informacje na temat niektórych dzia³añ symulatora. Informacje które mo¿na uzysk¹æ wymienione przy opisie klasy CrossroadInformation.
	*/
	void simulate();
	CrossroadInformation & getData();
};

#endif

