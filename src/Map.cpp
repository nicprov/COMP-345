#include "Map.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


//*********************************** TERRITORY *****************************************

//Default Constructor
Territory::Territory()
{
	terrIndex = 0;
	terrName = "";
	contIndex = 0;
}

//Parameterized constructor
Territory::Territory(int tid, string tn, int contID)
{
	terrIndex = tid;
	terrName = tn;
	contIndex = contID;
}

//Copy Constructor
Territory::Territory(const Territory& t)
{
	terrIndex = t.terrIndex;
	terrName = t.terrName;
	contIndex = t.contIndex;
	listOfAdjTerr = t.listOfAdjTerr;

}

//Assignment Operator
Territory& Territory:: operator = (const Territory& t)
{
	if (&t != this)
	{
		terrIndex = t.terrIndex;
		terrName = t.terrName;
		contIndex = t.contIndex;
		listOfAdjTerr = t.listOfAdjTerr;
	}
	return *this;
}

//Destructor
Territory::~Territory()
{
	for (int i = 0; i < this->listOfAdjTerr.size(); i++)
	{
		this->listOfAdjTerr[i] = nullptr;
	}
	this->listOfAdjTerr.clear();
}

int Territory::getTerrIndex()
{
	return terrIndex;
}

string Territory::getTerrName()
{
	return terrName;
}

int Territory::getContIndex()
{
	return contIndex;
}

void Territory::setTerrIndex(int tid)
{
	terrIndex = tid;
}

void Territory::setTerrName(string tn)
{
	terrName = tn;
}

void Territory::setContIndex(int contID)
{
	contIndex = contID;
}

Territory* Territory::getAdjTerritoryByName(string name)
{
	for (int i = 0; i < this->listOfAdjTerr.size(); i++)
	{
		if (this->listOfAdjTerr.at(i)->getTerrName() == name)
			return this->listOfAdjTerr.at(i);
	}
}

void Territory::printAdjTerritory()
{
	cout << "Adjacent Territories of Territory " << this->getTerrName() << ": ";
	for (int i = 0; i < this->listOfAdjTerr.size(); i++)
	{
		cout << this->listOfAdjTerr.at(i)->getTerrName() << " ";
	}
	cout << endl;
}

//Output Stream
ostream& operator << (ostream& out, const Territory& t)
{
	out << "The Territory name is '" << t.terrName << "'\n\n";
	cout << "Adjacent Territories of '" << t.terrName << "':";
	for (int i = 0; i < t.listOfAdjTerr.size(); i++)
	{
		cout << t.listOfAdjTerr.at(i)->terrName << " -> ";
	}
	cout << "\nContinent " << t.contIndex << ", Territory " << t.terrIndex << endl;

	return out;
}

//*********************************** CONTINENT *****************************************

//Default Constructor
Continent::Continent()
{
	cIndex = 0;
	contName = "";
	armyValue = 0;
}

//Parameterized constructor
Continent::Continent(int cid, string cn, int armyV)
{
	cIndex = cid;
	contName = cn;
	armyValue = armyV;
}

//Copy Constructor
Continent::Continent(const Continent& c)
{
	cIndex = c.cIndex;
	contName = c.contName;
	armyValue = c.armyValue;
	listOfAdjCont = c.listOfAdjCont;
	listOfTerritories = c.listOfTerritories;

}

//Assignment Operator
Continent& Continent:: operator = (const Continent& c)
{
	if (&c != this)
	{
		cIndex = c.cIndex;
		contName = c.contName;
		armyValue = c.armyValue;
		listOfAdjCont = c.listOfAdjCont;
		listOfTerritories = c.listOfTerritories;
	}
	return *this;
}

//Destructor
Continent::~Continent()
{
	for (int i = 0; i < this->listOfTerritories.size(); i++)
	{
		delete this->listOfTerritories[i];
		this->listOfTerritories[i] = nullptr;
	}
	this->listOfTerritories.clear();

	for (int i = 0; i < this->listOfAdjCont.size(); i++)
	{
		this->listOfAdjCont[i] = nullptr;
	}
	this->listOfAdjCont.clear();
}

int Continent::getCIndex()
{
	return cIndex;
}

string Continent::getContName()
{
	return contName;
}

int Continent::getArmyValue()
{
	return armyValue;
}

void Continent::setCIndex(int cid)
{
	cIndex = cid;
}

void Continent::setContName(string cn)
{
	contName = cn;
}

void Continent::setArmyValue(int armyV)
{
	armyValue = armyV;
}

void Continent::addTerritory(Territory* t)
{
	listOfTerritories.push_back(t);
}


Territory* Continent::getTerritory(int id)
{
	for (int i = 0; i < listOfTerritories.size(); i++)
	{
		if (listOfTerritories[i]->getContIndex() == id)
			return listOfTerritories[i];
	}

	return nullptr;
}

//Output Stream
ostream& operator << (ostream& out, const Continent& c)
{
	out << "The continent name is '" << c.contName << "'\n\n";

	out << "List of Territories of '" << c.contName << "' (id, name)\n\n";
	for (int i = 0; i < c.listOfTerritories.size(); i++)
	{
		out << i + 1 << ". " << c.listOfTerritories.at(i)->getTerrIndex() << ", " << c.listOfTerritories.at(i)->getTerrName() << endl;
	}

	return out;
}


//*********************************** MAP *****************************************

//Default Constructor
Map::Map()
{
	mapName = "";
}

//Parameterized constructor
Map::Map(string mn)
{
	mapName = mn;
}

//Copy Constructor
Map::Map(const Map& m)
{
	mapName = m.mapName;
	listOfContinents = m.listOfContinents;
}

//Assignment Operator
Map& Map:: operator = (const Map& m)
{
	if (&m != this)
	{
		mapName = m.mapName;
		listOfContinents = m.listOfContinents;
		listOfTerritories = m.listOfTerritories;
	}
	return *this;
}

//Destructor
Map::~Map()
{
	for (int i = 0; i < this->listOfContinents.size(); i++)
	{
		delete this->listOfContinents[i];
		this->listOfContinents[i] = nullptr;
	}
	this->listOfContinents.clear();

	for (int i = 0; i < this->listOfTerritories.size(); i++)
	{
		this->listOfTerritories[i] = nullptr;
	}
	this->listOfTerritories.clear();
}

string Map::getMapName()
{
	return mapName;
}

void Map::setMapName(string mn)
{
	mapName = mn;
}

void Map::addContinent(Continent* c)
{
	listOfContinents.push_back(c);
}

void Map::addTerritory(Territory* t)
{
	listOfTerritories.push_back(t);
}

void Map::addAdjTerritory(Territory* t1, Territory* t2)
{
	t1->listOfAdjTerr.push_back(t2);
}

void Map::addAdjContinent(Continent* c1, Continent* c2)
{
	c1->listOfAdjCont.push_back(c2);
}

Continent* Map::getContinent(int cid)
{
	return listOfContinents[cid - 1];
}

Territory* Map::getTerritory(int tid)
{
	return listOfTerritories[tid - 1];
}


void Map::traverse(Territory* current, bool visitedT[], bool visitedC[])
{
	if (!visitedT[current->getTerrIndex() - 1])
	{
		visitedT[current->getTerrIndex() - 1] = true;

		if (current->getContIndex() != NULL && !visitedC[current->getContIndex() - 1])
		{
			visitedC[current->getContIndex() - 1] = true;
		}

		for (Territory* neighbor : listOfTerritories.at(current->getTerrIndex() - 1)->listOfAdjTerr)
		{
			traverse(neighbor, visitedT, visitedC);
		}
	}
}


void Map::checkOnly1(Continent* current, bool visCont[], int terrCount[])
{
	if (!visCont[current->getCIndex() - 1])
	{
		visCont[current->getCIndex() - 1] = true;
		
		for (int i = 0; i < listOfTerritories.size(); i++)
		{
			if (listOfTerritories[i]->getContIndex() == current->getCIndex())
				terrCount[i] += 1;
		}

		for (int j=current->getCIndex(); j < listOfContinents.size(); j++)
		{
			checkOnly1(listOfContinents.at(j), visCont, terrCount);
		}
	}
}

//Validate 1) the map is a connected graph, 2) continents are connected subgraphs and 3) each country belongs to one and only one continent.

bool Map::validate()
{
	bool tIsConnected = true;
	bool cIsConnected = true;
	bool only1Cont = true;

	bool* visitedT = new bool[listOfTerritories.size()]{ false };
	bool* visitedC = new bool[listOfContinents.size()]{ false };
	bool* visCont = new bool[listOfContinents.size()]{ false };
	int* terrCount = new int[listOfTerritories.size()]{ 0 };

	traverse(listOfTerritories.at(0), visitedT, visitedC);
	checkOnly1(listOfContinents.at(0), visCont, terrCount);

	for (int i = 0; i < listOfTerritories.size(); i++)
	{
		if (!visitedT[i])
		{
			tIsConnected = false;
		}
	}

	for (int j = 0; j < listOfContinents.size(); j++)
	{
		if (!visitedC[j])
		{
			cIsConnected = false;
		}
	}

	for (int k = 0; k < listOfTerritories.size(); k++)\
	{
		if (terrCount[k] != 1)
		{
			only1Cont = false;
		}
	}

	delete[] visitedT;
	delete[] visitedC;
	delete[] visCont;
	delete[] terrCount;

	if (tIsConnected && cIsConnected && only1Cont)
	{
		cout << "Map is a connected graph.\nContinents are connected subgraphs.\nEach territory belongs to one and only one continent.\n";
		return true;
	}
	else if (tIsConnected && cIsConnected && !only1Cont)
	{
		cout << "Map is a connected graph.\nContinents are connected subgraphs.\nEach territory does not belong to one and only one continent.\n";
		return false;
	}
	else if (tIsConnected && !cIsConnected && only1Cont)
	{
		cout << "Map is a connected graph.\nContinents are not connected subgraphs.\nEach territory belongs to one and only one continent.\n";
		return false;
	}
	else if (!tIsConnected && cIsConnected && only1Cont)
	{
		cout << "Map is not a connected graph.\nContinents are connected subgraphs.\nEach territory belongs to one and only one continent.\n";
		return false;
	}
	else if (!tIsConnected && !cIsConnected && only1Cont)
	{
		cout << "Map is not a connected graph.\nContinents are not connected subgraphs.\nEach territory belongs to one and only one continent.\n";
		return false;
	}
	else if (!tIsConnected && cIsConnected && !only1Cont)
	{
		cout << "Map is not a connected graph.\nContinents are connected subgraphs.\nEach territory does not belong to one and only one continent.\n";
		return false;
	}
	else if (tIsConnected && !cIsConnected && !only1Cont)
	{
		cout << "Map is a connected graph.\nContinents are not connected subgraphs.\nEach territory does not belong to one and only one continent.\n";
		return false;
	}
	else
	{
		cout << "Map is not a connected graph.\nContinents are not connected subgraphs.\nEach territory does not belong to one and only one continent.\n";
		return false;
	}

}

//Output Stream
ostream& operator << (ostream& out, const Map& m)
{
	out << "The map name is '" << m.mapName << "'\n\n";

	out << "List of Continents of '" << m.mapName << "' and their Territories (id, name)\n\n";
	
	for (int i = 0; i < m.listOfContinents.size(); i++)
	{
		out << m.listOfContinents.at(i)->getCIndex() << ", " << m.listOfContinents.at(i)->getContName() << endl;

		out << "List of Territories of '" << m.listOfContinents.at(i)->getContName() << "'" << endl;
		for (int j = 0; j < m.listOfContinents.at(i)->listOfTerritories.size(); j++)
		{
			out << "   " << j + 1 << ". " << m.listOfContinents.at(i)->listOfTerritories.at(j)->getTerrIndex() << ", " <<
				m.listOfContinents.at(i)->listOfTerritories.at(j)->getTerrName() << endl;
		}
		out << endl;
	}

	return out;
}

//*********************************** MAP LOADER *****************************************

//Default Constructor
MapLoader::MapLoader()
{
	this->mapFileName = nullptr;
}

//Copy Constructor
MapLoader::MapLoader(MapLoader& map)
{
	mapFileName = map.mapFileName;
}

//Assignment Operator
MapLoader& MapLoader:: operator = (const MapLoader& map)
{
	return *this;
}

//Destructor
MapLoader::~MapLoader()
{
	delete mapFileName;
}

//Parameterized constructor
MapLoader::MapLoader(string mapFileName)
{
	this->mapFileName = new string(mapFileName);
}

//Method to read map file
Map* MapLoader::GetMap(Map* map, string filename)
{
	return ReadMap(map, filename);
}

Map* MapLoader::ReadMap(Map* map, string mapFileName)
{
	try
	{
		Continent* newContinent;
		Territory* newTerritory;
		string line = "";
		bool hasContinent = false;
		bool hasTerritory = false;
		bool hasAdj = false;

		ifstream inStream;
		inStream.open(mapFileName);

		if (inStream.fail())
		{
			cout << "Error! File could not be read. \n";
			return nullptr;
		}
		else
		{
			while (getline(inStream, line))
			{
				if (line.find("[continents]") == 0)
				{
					getline(inStream, line);

					int index = 1;

					while (line.find("[countries]") != 0)
					{
						if (line == "")
							break;

						//Split line to access different attributes of continents
						vector<string> attributes = SplitString(line);
						newContinent = new Continent(index /*stores continent id*/, attributes[0]/*stores continent name*/, stoi(attributes[1])/*stores army value as an integer*/);
						map->addContinent(newContinent);
						cout << "New Continent: " << index << " " << attributes[0] << " " << attributes[1] << endl;
						index++;
						getline(inStream, line);
					}

					cout << endl;
					hasContinent = true;
				}

				if (line.find("[countries]") == 0 && hasContinent)
				{
					getline(inStream, line);

					while (line.find("[borders]") != 0)
					{
						if (line == "")
							break;

						vector<string> attributes = SplitString(line);
						newTerritory = new Territory(stoi(attributes[0])/*stores territory id as an integer*/, attributes[1] /*stores territory name*/, stoi(attributes[2])/*stores the continent id the territory belongs to as an integer*/);
						map->listOfContinents[stoi(attributes[2]) - 1]->addTerritory(newTerritory); //adds the territory to a continent.
						map->addTerritory(newTerritory); //adds the territory to list of all territories.

						cout << "New Territory: " << attributes[0] << " " << attributes[1] << " " << attributes[2] << endl;
						getline(inStream, line);
					}

					hasTerritory = true;
				}

				if (line.find("[borders]") == 0 && hasContinent && hasTerritory)
				{
					getline(inStream, line);
					while (!line.empty())
					{
						if (line == "")
							break;

						vector<string> adjTerritories = SplitString(line);
						Territory* t1 = map->getTerritory(stoi(adjTerritories[0]));
						cout << "\nNew Border: " << adjTerritories[0];
						for (int i = 1; i < adjTerritories.size(); i++)
						{
							Territory* t2 = map->getTerritory(stoi(adjTerritories[i]));
							map->addAdjTerritory(t1, t2);

							cout << " " << adjTerritories[i];
						}


						getline(inStream, line);
					}

					hasAdj = true;
				}
			}

			if (hasContinent && hasTerritory && hasAdj)
			{
				cout << "\n\nThe Map is valid. \n";
				inStream.close();
				return map;
			}
			else
			{
				cout << "\n\nThe Map is invalid \n";
				inStream.close();
				return nullptr;
			}
		}
	}

	catch (const exception& e)
	{
		return nullptr;
		cerr << "An Error has occured! \n";
	}
}

// Code taken from ideone.com/R9RJCf
vector<string> MapLoader::SplitString(string s)
{
	istringstream iss(s);
	vector<string> v;
	while (iss >> s)
	{
		v.push_back(s);
	}

	return v;
}

//Output Stream
ostream& operator << (std::ostream& o, const MapLoader& ml)
{
	return o << "This is a domination map: " << ml.mapFileName;
}

