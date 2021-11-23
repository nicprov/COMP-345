#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "Player.h"

class Player;

class Territory
{
public:
    Territory(); //Default constructor
    Territory(int tid, std::string tn, int contID); //Parameterized constructor
    Territory(int tid, std::string tn, int contID, int numArmies, Player* p); //Parameterized constructor
    Territory(const Territory& t); //Copy constructor
    Territory& operator = (const Territory& t); //Assignment operator
    ~Territory(); //Destructor

    int getTerrIndex(); //Get the territory index
    std::string getTerrName(); //Get the territory name
    int getContIndex(); //Get the continent index
    int getNumberOfArmies(); //Get the number of armies

    void setTerrIndex(int tid); //Set the territory index
    void setTerrName(std::string tn); //Set the territory name
    void setContIndex(int contID); //Set the continent index
    void setNumberOfArmies(int numArmies); //Set the number of armies

    void printAdjTerritory(); //Print list of adjacent territories
    Territory* getAdjTerritoryByName(std::string name); //Get the name of adjacent territories
    friend std::ostream& operator << (std::ostream& out, const Territory& c); //Stream output operator
    friend std::ostream& operator << (std::ostream& out, std::vector<Territory*>); //Stream output operator
    bool operator== (const Territory&) const; //Check if 2 territories are the same

    Player* getOwner(); // get owner of a Territory
    void setOwner(Player* p); //set owner of a Territory
    Player* getOwnerOfAdj(std::string terrName); //get the owner of an adjacent Territory
    bool addTroops(int numTroops); //add armies to a Territory
    bool removeTroops(int numTroops); //remove armies from a Territory
    bool isAdjacent(std::string terrName); //check if Territory is adjacent

    std::vector<Territory*> listOfAdjTerr; //Vector contaning adjacent territories

private:
    int terrIndex; //territory index
    std::string terrName; //territory name
    int contIndex; //continent index
    int numberOfArmies; //number of armies in a given Territory
    Player* owner; //owner of a territory
    std::string name; //name
    int army; //number of armies
};


class Continent
{
public:
    Continent(); //Default constructor
    Continent(int cid, std::string cn, int armyV); //Parameterized constructor
    Continent(const Continent& c); //Copy constructor
    Continent& operator = (const Continent& c); //Assignment operator
    ~Continent(); //Destructor

    int getCIndex(); //Get the continent index
    std::string getContName(); //Get the continent name
    int getArmyValue(); //Get the army value

    void setCIndex(int cid); //Set the continent index
    void setContName(std::string cn); //Set the continent name
    void setArmyValue(int armyV); //Set the army value

    void addTerritory(Territory* t); //Add a territory
    Territory* getTerritory(int tid); //Get a territory
    friend std::ostream& operator << (std::ostream& out, const Continent& c); //Stream output operator
    bool operator== (const Continent&) const; //Check if 2 continents are the same
    bool isOwnedByPlayer(Player*); //Check if the continent is owned by a player

    std::vector<Continent*> listOfAdjCont; //vector of adjacent continents
    std::vector<Territory*> listOfTerritories; //vector of territories

private:
    int cIndex; //continent index
    std::string contName; //continent name
    int armyValue; //army value
};


class Map
{
public:
    Map(); //Default constructor
    Map(std::string mn); //Parameterized constructor
    Map(const Map& m); //Copy constructor
    Map& operator = (const Map& m); //Assignment operator
    ~Map(); //Destructor

    std::string getMapName(); //Get the name of the map
    void setMapName(std::string mn); //Set the name of the map

    void addContinent(Continent* c); //Add a continent
    void addTerritory(Territory* t); //Add a territory
    void addAdjContinent(Continent* c1, Continent* c2); //Add an adjacent continent
    void addAdjTerritory(Territory* t1, Territory* t2); //Add an adjacent territory
    Continent* getContinent(int cid); //Get a contient
    Territory* getTerritory(int tid); //Get a territory
    void traverse(Territory* current, bool visitedT[], bool visitedC[]); //Traverses the map to check if it is a graph and the the continents are a subgraph
    void checkOnly1(Continent* current, bool visCont[], int terrCount[]); //Checks if each country belongs to one and only one continent
    bool validate(); //Check if the map is valid
    friend std::ostream& operator << (std::ostream& out, const Map& m); //Stream output operator
    bool operator== (const Map&) const; //Check if 2 maps are the same
    std::vector<Territory*> getTerritoriesByPlayer(Player*); //vector containing list of player territories

    std::vector<Continent*> listOfContinents; //vector of continents
    std::vector<Territory*> listOfTerritories; //vector of territories

private:
    std::string mapName; //Name of map file
};


class MapLoader
{
public:
    MapLoader(); //Default constructor
    MapLoader(MapLoader&); //Copy constructor
    MapLoader& operator = (const MapLoader& map); //Assignment operator
    ~MapLoader(); //Destructor

    MapLoader(std::string mapFileName); //Parameterized constructor
    void readMap(Map* map); //Read map file
    friend std::ostream& operator<<(std::ostream& o, const MapLoader& ml); //Stream output operator

    std::vector<std::string> splitString(std::string s); //Split string read from file

private:
    std::string mapFileName; //name of map file
};
