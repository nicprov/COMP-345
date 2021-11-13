#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "Player.h"

class Player;

using namespace std;

class Territory
{
public:
    Territory(); //Default constructor
    Territory(int tid, string tn, int contID); //Parameterized constructor
    Territory(int tid, string tn, int contID, int numArmies, Player* p); //Parameterized constructor
    Territory(const Territory& t); //Copy constructor
    Territory& operator = (const Territory& t); //Assignment operator
    ~Territory(); //Destructor

    int getTerrIndex(); //Get the territory index
    string getTerrName(); //Get the territory name
    int getContIndex(); //Get the continent index
    int getNumberOfArmies(); //Get the number of armies

    void setTerrIndex(int tid); //Set the territory index
    void setTerrName(string tn); //Set the territory name
    void setContIndex(int contID); //Set the continent index
    void setNumberOfArmies(int numArmies); //Set the number of armies

    void printAdjTerritory(); //Print list of adjacent territories
    Territory* getAdjTerritoryByName(string name); //Get the name of adjacent territories
    friend ostream& operator << (ostream& out, const Territory& c); //Stream output operator
    friend ostream& operator << (ostream& out, std::vector<Territory*>); //Stream output operator
    bool operator== (const Territory&) const; //Check if 2 territories are the same

    Player* getOwner(); // get owner of a Territory
    void setOwner(Player* p); //set owner of a Territory
    Player* getOwnerOfAdj(string terrName); //get the owner of an adjacent Territory
    bool addTroops(int numTroops); //add armies to a Territory
    bool removeTroops(int numTroops); //remove armies from a Territory
    bool isAdjacent(string terrName); //check if Territory is adjacent

    vector<Territory*> listOfAdjTerr; //Vector contaning adjacent territories

private:
    int terrIndex; //territory index
    string terrName; //territory name
    int contIndex; //continent index
    int numberOfArmies; //number of armies in a given Territory
    Player* owner; //owner of a territory
    string name; //name 
    int army; //number of armies
};


class Continent
{
public:
    Continent(); //Default constructor
    Continent(int cid, string cn, int armyV); //Parameterized constructor
    Continent(const Continent& c); //Copy constructor
    Continent& operator = (const Continent& c); //Assignment operator
    ~Continent(); //Destructor

    int getCIndex(); //Get the continent index
    string getContName(); //Get the continent name
    int getArmyValue(); //Get the army value

    void setCIndex(int cid); //Set the continent index
    void setContName(string cn); //Set the continent name
    void setArmyValue(int armyV); //Set the army value

    void addTerritory(Territory* t); //Add a territory
    Territory* getTerritory(int tid); //Get a territory
    friend ostream& operator << (ostream& out, const Continent& c); //Stream output operator
    bool operator== (const Continent&) const; //Check if 2 continents are the same
    bool isOwnedByPlayer(Player*); //Check if the continent is owned by a player

    vector<Continent*> listOfAdjCont; //vector of adjacent continents
    vector<Territory*> listOfTerritories; //vector of territories

private:
    int cIndex; //continent index
    string contName; //continent name
    int armyValue; //army value
};


class Map
{
public:
    Map(); //Default constructor
    Map(string mn); //Parameterized constructor
    Map(const Map& m); //Copy constructor
    Map& operator = (const Map& m); //Assignment operator
    ~Map(); //Destructor

    string getMapName(); //Get the name of the map
    void setMapName(string mn); //Set the name of the map

    void addContinent(Continent* c); //Add a continent
    void addTerritory(Territory* t); //Add a territory
    void addAdjContinent(Continent* c1, Continent* c2); //Add an adjacent continent
    void addAdjTerritory(Territory* t1, Territory* t2); //Add an adjacent territory
    Continent* getContinent(int cid); //Get a contient
    Territory* getTerritory(int tid); //Get a territory
    void traverse(Territory* current, bool visitedT[], bool visitedC[]); //Traverses the map to check if it is a graph and the the continents are a subgraph
    void checkOnly1(Continent* current, bool visCont[], int terrCount[]); //Checks if each country belongs to one and only one continent
    bool validate(); //Check if the map is valid
    friend ostream& operator << (ostream& out, const Map& m); //Stream output operator
    bool operator== (const Map&) const; //Check if 2 maps are the same
    vector<Territory*> getTerritoriesByPlayer(Player*); //vector containing list of player territories

    vector<Continent*> listOfContinents; //vector of continents
    vector<Territory*> listOfTerritories; //vector of territories

private:
    string mapName; //Name of map file
};


class MapLoader
{
public:
    MapLoader(); //Default constructor
    MapLoader(MapLoader&); //Copy constructor
    MapLoader& operator = (const MapLoader& map); //Assignment operator
    ~MapLoader(); //Destructor

    MapLoader(string mapFileName); //Parameterized constructor
    void readMap(Map* map); //Read map file
    friend ostream& operator<<(std::ostream& o, const MapLoader& ml); //Stream output operator

    vector<string> splitString(string s); //Split string read from file

private:
    string mapFileName; //name of map file
};
