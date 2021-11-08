#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Player.h"

using namespace std;

class Player;

class Territory
{
public:
    Territory();
    Territory(int tid, string tn, int contID);
    Territory(const Territory& t);
    Territory& operator = (const Territory& t);
    ~Territory();

    int getTerrIndex();
    string getTerrName();
    int getContIndex();

    void setTerrIndex(int tid);
    void setTerrName(string tn);
    void setContIndex(int contID);

    void printAdjTerritory();
    Territory* getAdjTerritoryByName(string name);
    friend ostream& operator << (ostream& out, const Territory& c);
    friend ostream& operator << (ostream& out, const std::vector<Territory*>);
    bool operator== (const Territory&) const;


    Player* getOwner(); // get owner of this Territory
    void setOwner(Player* p); //set owner of a Territory
    Player* getOwnerOfAdj(string terrName); //get the owner of an adjacent Territory
    bool addTroops(int numTroops); //add armies to a Territory
    bool removeTroops(int numTroops); //remove armies from a Territory

    vector<Territory*> listOfAdjTerr;
    int numberOfArmies; //number of armies in a given Territory

private:
    int terrIndex;
    string terrName;
    int contIndex;

    Player* owner; //player that owns a given Territory
};


class Continent
{
public:
    Continent();
    Continent(int cid, string cn, int armyV);
    Continent(const Continent& c);
    Continent& operator = (const Continent& c);
    ~Continent();

    int getCIndex();
    string getContName();
    int getArmyValue();

    void setCIndex(int cid);
    void setContName(string cn);
    void setArmyValue(int armyV);

    void addTerritory(Territory* t);
    Territory* getTerritory(int tid);
    friend ostream& operator << (ostream& out, const Continent& c);
    bool operator== (const Continent&) const;

    vector<Continent*> listOfAdjCont;
    vector<Territory*> listOfTerritories;

private:
    int cIndex;
    string contName;
    int armyValue;
};


class Map
{
public:
    Map();
    Map(string mn);
    Map(const Map& m);
    Map& operator = (const Map& m);
    ~Map();

    string getMapName();
    void setMapName(string mn);

    void addContinent(Continent* c);
    void addTerritory(Territory* t);
    void addAdjContinent(Continent* c1, Continent* c2);
    void addAdjTerritory(Territory* t1, Territory* t2);
    Continent* getContinent(int cid);
    Territory* getTerritory(int tid);
    void traverse(Territory* current, bool visitedT[], bool visitedC[]);
    void checkOnly1(Continent* current, bool visCont[], int terrCount[]);
    bool validate();
    friend ostream& operator << (ostream& out, const Map& m);
    bool operator== (const Map&) const;

    vector<Continent*> listOfContinents;
    vector<Territory*> listOfTerritories;

private:
    string mapName;
};


class MapLoader
{
public:
    MapLoader();
    MapLoader(MapLoader& map);
    MapLoader& operator = (const MapLoader& map);
    ~MapLoader();

    MapLoader(string mapFileName);
    virtual Map* GetMap(Map* map, string filename);
    Map* ReadMap(Map* map, string mapFileName);
    friend ostream& operator<<(std::ostream& o, const MapLoader& ml);

    vector<string> SplitString(string s);

private:
    string* mapFileName;
};



