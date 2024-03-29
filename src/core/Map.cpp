#include <string>
#include <vector>
#include <iostream>
#include "Map.h"

//*********************************** TERRITORY *****************************************

/**
 * Default Constructor
 */
Territory::Territory()
{
    terrIndex = 0;
    terrName = "";
    contIndex = 0;
}

/**
 * Parameterized constructor
 * @param tid Territory Id
 * @param tn Territory Name
 * @param contID Corresponding continent id to the territory.
 */

Territory::Territory(int tid, std::string tn, int contID)
{
    terrIndex = tid;
    terrName = tn;
    contIndex = contID;
}

/**
 * Parameterized constructor
 * @param tid Territory Id
 * @param tn Territory Name
 * @param contID Corresponding continent id to the territory.
 * @param numArmies number of armies in a territory
 * @param p player owning the territory
 */
Territory::Territory(int tid, std::string tn, int contID, int numArmies, Player* p)
{
    terrIndex = tid;
    terrName = tn;
    contIndex = contID;
    numberOfArmies = numArmies;
    owner = p;
}

/**
 * Copy Constructor makes a copy of Territory.
 * @param t Territory
 */
Territory::Territory(const Territory& t)
{
    terrIndex = t.terrIndex;
    terrName = t.terrName;
    contIndex = t.contIndex;
    numberOfArmies = t.numberOfArmies;
    owner = t.owner;
    listOfAdjTerr = t.listOfAdjTerr;
}

/**
 * Assignment Operator
 * @param t Territory
 */
Territory& Territory:: operator = (const Territory& t)
{
    if (&t != this)
    {
        terrIndex = t.terrIndex;
        terrName = t.terrName;
        contIndex = t.contIndex;
        numberOfArmies = t.numberOfArmies;
        owner = t.owner;
        listOfAdjTerr = t.listOfAdjTerr;
    }
    return *this;
}

/**
 * Destructor
 * Destroys the list of adjacent territories.
 */
Territory::~Territory()= default;

/**
 * Get the territory index
 */
int Territory::getTerrIndex()
{
    return terrIndex;
}

/**
 * Get the territory name
 */
std::string Territory::getTerrName()
{
    return terrName;
}

/**
 * Get the continent index
 */
int Territory::getContIndex()
{
    return contIndex;
}

/**
 * Get the number of armies
 */
int Territory::getNumberOfArmies()
{
    return numberOfArmies;
}

/**
 * Set the territory index
 */
void Territory::setTerrIndex(int tid)
{
    terrIndex = tid;
}

/**
 * Set the territory name
 */
void Territory::setTerrName(std::string tn)
{
    terrName = tn;
}

/**
 * Set the contient index
 */
void Territory::setContIndex(int contID)
{
    contIndex = contID;
}

/**
 * Set the number of armies
 */
void Territory::setNumberOfArmies(int numArmies)
{
    numberOfArmies = numArmies;
}

/**
 * Get the name of adjacent territories
 */
Territory* Territory::getAdjTerritoryByName(std::string name)
{
    for (int i = 0; i < this->listOfAdjTerr.size(); i++)
    {
        if (this->listOfAdjTerr.at(i)->getTerrName() == name)
            return this->listOfAdjTerr.at(i);
    }
    return 0;
}

/**
 * Prints the list of adjacent territories.
 */
void Territory::printAdjTerritory()
{
    std::cout << "Adjacent Territories of Territory " << this->getTerrName() << ": ";
    for (int i = 0; i < this->listOfAdjTerr.size(); i++)
    {
        std::cout << this->listOfAdjTerr.at(i)->getTerrName() << " ";
    }
    std::cout << std::endl;
}

/**
 * Output Stream for Territories.
 */
std::ostream& operator << (std::ostream& out, const Territory& t)
{
    return out << "Territory# " << t.terrIndex << "[" << t.terrName << ", Armies <" << t.numberOfArmies << ">, Owner <" << t.owner->getName() << "]";
}

/**
 * Check if 2 territories are the same
 */
bool Territory::operator==(const Territory &territory) const {
    return this->listOfAdjTerr == territory.listOfAdjTerr && this->terrName == territory.terrName && this->contIndex == territory.contIndex && this->terrIndex == territory.terrIndex && this->owner == territory.owner && this->numberOfArmies == territory.numberOfArmies;
}

/**
 * Stream output operator
 */
std::ostream &operator<<(std::ostream &out, const std::vector<Territory*> territoryList) {
    if (territoryList.empty())
        return out << "No territories in list";

    int count = 1;
    for (Territory* territory: territoryList){
        out << count++ << ". " << *territory << std::endl;
    }
    return out;
}

/**
 * Get the owner of a Territory.
 */
Player* Territory::getOwner()
{
    return this->owner;
}

/**
* Set the owner of a Territory.
*/
void Territory::setOwner(Player* p)
{
    this->owner = p;
}

/**
* Returns the name of the owner of an adjacent Territory.
*/
Player* Territory::getOwnerOfAdj(std::string terrName)
{
    for (int i = 0; i < listOfAdjTerr.size(); i++)
    {
        if (listOfAdjTerr.at(i)->getTerrName() == terrName)
            return listOfAdjTerr.at(i)->owner;
    }
    return nullptr;
}

/**
* Adds armies to a Territory. Returns false if the number entered is negative.
*/
bool Territory::addTroops(int numTroops)
{
    if (numTroops > 0)
    {
        numberOfArmies += numTroops;
        return true;
    }
    return false;
}

/**
* Removes armies from a Territory. Returns false if the number entered is negative.
*/
bool Territory::removeTroops(int numTroops)
{
    if (numTroops > 0)
    {
        numberOfArmies -= numTroops;
        return true;
    }
    return false;
}

bool Territory::isAdjacent(std::string terrName)
{
    for (int i = 0; i < listOfAdjTerr.size(); i++)
    {
        if (listOfAdjTerr.at(i)->getTerrName() == terrName)
            return true;
    }

    return false;
}

//*********************************** CONTINENT *****************************************

/**
 * Default Constructor
 */
Continent::Continent()
{
    cIndex = 0;
    contName = "";
    armyValue = 0;
}

/**
 * Parameterized constructor
 * @param cid Continent Id
 * @param cn Continent Name
 * @param armyV Army value of the continent.
 */
Continent::Continent(int cid, std::string cn, int armyV)
{
    cIndex = cid;
    contName = cn;
    armyValue = armyV;
}

/**
 * Copy Constructor makes a copy of Continent.
 * @param c Continent
 */
Continent::Continent(const Continent& c)
{
    cIndex = c.cIndex;
    contName = c.contName;
    armyValue = c.armyValue;
    listOfAdjCont = c.listOfAdjCont;
    listOfTerritories = c.listOfTerritories;

}

/**
 * Assignment Operator
 * @param c Continent
 */
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

/**
 * Destructor
 * Destroys the list of territories and the list of adjacent continents.
 */
Continent::~Continent()
{
    for (Territory* territory: this->listOfTerritories)
        delete territory;
}

/**
 * Get the continent index
 */
int Continent::getCIndex()
{
    return cIndex;
}

/**
 * Get the continent name
 */
std::string Continent::getContName()
{
    return contName;
}

/**
 * Get the army value of a continent
 */
int Continent::getArmyValue()
{
    return armyValue;
}

/**
 * Set the continent index
 */
void Continent::setCIndex(int cid)
{
    cIndex = cid;
}

/**
 * Set the continent name
 */
void Continent::setContName(std::string cn)
{
    contName = cn;
}

/**
 * Set the army value
 */
void Continent::setArmyValue(int armyV)
{
    armyValue = armyV;
}

/**
 * Add a territory
 */
void Continent::addTerritory(Territory* t)
{
    listOfTerritories.push_back(t);
}

/**
 * Get a territory
 */
Territory* Continent::getTerritory(int id)
{
    for (int i = 0; i < listOfTerritories.size(); i++)
    {
        if (listOfTerritories[i]->getContIndex() == id)
            return listOfTerritories[i];
    }

    return nullptr;
}

/**
 * Output Stream for Continents
 */
std::ostream& operator << (std::ostream& out, const Continent& c)
{
    out << "The continent name is '" << c.contName << "'\n\n";

    out << "List of Territories of '" << c.contName << "' (id, name)\n\n";
    for (int i = 0; i < c.listOfTerritories.size(); i++)
    {
        out << i + 1 << ". " << c.listOfTerritories.at(i)->getTerrIndex() << ", " << c.listOfTerritories.at(i)->getTerrName() << std::endl;
    }

    return out;
}

/**
 * Check if 2 continents are the same
 */
bool Continent::operator==(const Continent &continent) const {
    return this->listOfTerritories == continent.listOfTerritories && this->contName == continent.contName && this->armyValue == continent.armyValue && this->cIndex == continent.cIndex && this->listOfAdjCont == continent.listOfAdjCont;
}

/**
 * Check if the continent is owned by a player
 */
bool Continent::isOwnedByPlayer(Player* player) {
    for (Territory* territory: this->listOfTerritories){
        if (territory->getOwner() != player)
            return false;
    }
    return true;
}

//*********************************** MAP *****************************************

/**
 * Default Constructor
 */
Map::Map()
{
    mapName = "";
}

/**
 * Parameterized constructor
 * @param mn Map name
 */
Map::Map(std::string mn)
{
    mapName = mn;
}

/**
 * Copy Constructor makes a copy of Map.
 * @param m Map
 */
Map::Map(const Map& m)
{
    mapName = m.mapName;
    listOfContinents = m.listOfContinents;
}

/**
 * Assignment Operator
 * @param m Map
 */
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

/**
 * Destructor
 * Destroys the list of continents and the list of territories.
 */
Map::~Map()
{
    for (Continent* continent: this->listOfContinents)
        delete continent;
}

/**
 * Get the name of the map
 */
std::string Map::getMapName()
{
    return mapName;
}

/**
 * Set the name of the map
 */
void Map::setMapName(std::string mn)
{
    mapName = mn;
}

/**
 * Add a continent
 */
void Map::addContinent(Continent* c)
{
    listOfContinents.push_back(c);
}

/**
 * Add a territory
 */
void Map::addTerritory(Territory* t)
{
    listOfTerritories.push_back(t);
}

/**
 * Add an adjacent territory
 */
void Map::addAdjTerritory(Territory* t1, Territory* t2)
{
    t1->listOfAdjTerr.push_back(t2);
}

/**
 * Add an adjacent continent
 */
void Map::addAdjContinent(Continent* c1, Continent* c2)
{
    c1->listOfAdjCont.push_back(c2);
}

/**
 * Get a contient
 */
Continent* Map::getContinent(int cid)
{
    return listOfContinents[cid - 1];
}

/**
 * Get a territory
 */
Territory* Map::getTerritory(int tid)
{
    return listOfTerritories[tid - 1];
}

/**
 * Traverses the map to check if it is a graph and the the continents are a subgraph.
 * @param current Territory currently on.
 * @param visitedT Whether a Territory has been visited or not
 * @param visitedC Whether a Continent has been Visited or not
 */
void Map::traverse(Territory* current, bool visitedT[], bool visitedC[])
{
    if (!visitedT[current->getTerrIndex() - 1])
    {
        visitedT[current->getTerrIndex() - 1] = true;

        if (current->getContIndex() != 0 && !visitedC[current->getContIndex() - 1])
        {
            visitedC[current->getContIndex() - 1] = true;
        }

        for (Territory* neighbor : listOfTerritories.at(current->getTerrIndex() - 1)->listOfAdjTerr)
        {
            traverse(neighbor, visitedT, visitedC);
        }
    }
}

/**
 * Checks if each country belongs to one and only one continent.
 * @param current Continent currently on.
 * @param visCont Whether a Continent has been visited or not
 * @param terrCount Number of times a territory appears.
 */
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

/**
 * Validates
 * 1) the map is a connected graph,
 * 2) continents are connected subgraphs and
 * 3) each country belongs to one and only one continent.
 * @return if map is valid.
 */
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
        std::cout << "Map is a connected graph.\nContinents are connected subgraphs.\nEach territory belongs to one and only one continent.\n";
        return true;
    }
    else if (tIsConnected && cIsConnected && !only1Cont)
    {
        std::cout << "Map is a connected graph.\nContinents are connected subgraphs.\nEach territory does not belong to one and only one continent.\n";
        return false;
    }
    else if (tIsConnected && !cIsConnected && only1Cont)
    {
        std::cout << "Map is a connected graph.\nContinents are not connected subgraphs.\nEach territory belongs to one and only one continent.\n";
        return false;
    }
    else if (!tIsConnected && cIsConnected && only1Cont)
    {
        std::cout << "Map is not a connected graph.\nContinents are connected subgraphs.\nEach territory belongs to one and only one continent.\n";
        return false;
    }
    else if (!tIsConnected && !cIsConnected && only1Cont)
    {
        std::cout << "Map is not a connected graph.\nContinents are not connected subgraphs.\nEach territory belongs to one and only one continent.\n";
        return false;
    }
    else if (!tIsConnected && cIsConnected && !only1Cont)
    {
        std::cout << "Map is not a connected graph.\nContinents are connected subgraphs.\nEach territory does not belong to one and only one continent.\n";
        return false;
    }
    else if (tIsConnected && !cIsConnected && !only1Cont)
    {
        std::cout << "Map is a connected graph.\nContinents are not connected subgraphs.\nEach territory does not belong to one and only one continent.\n";
        return false;
    }
    else
    {
        std::cout << "Map is not a connected graph.\nContinents are not connected subgraphs.\nEach territory does not belong to one and only one continent.\n";
        return false;
    }

}

/**
 * Output Stream for Maps.
 */
std::ostream& operator << (std::ostream& out, const Map& m)
{
    out << "The map name is '" << m.mapName << "'\n\n";

    out << "List of Continents of '" << m.mapName << "' and their Territories (id, name)\n\n";

    for (int i = 0; i < m.listOfContinents.size(); i++)
    {
        out << m.listOfContinents.at(i)->getCIndex() << ", " << m.listOfContinents.at(i)->getContName() << std::endl;

        out << "List of Territories of '" << m.listOfContinents.at(i)->getContName() << "'" << std::endl;
        for (int j = 0; j < m.listOfContinents.at(i)->listOfTerritories.size(); j++)
        {
            out << "   " << j + 1 << ". " << m.listOfContinents.at(i)->listOfTerritories.at(j)->getTerrIndex() << ", " <<
                m.listOfContinents.at(i)->listOfTerritories.at(j)->getTerrName() << std::endl;
        }
        out << std::endl;
    }

    return out;
}

/**
 * Check if 2 maps are the same
 */
bool Map::operator==(const Map &map) const {
    return this->listOfContinents == map.listOfContinents && this->listOfTerritories == map.listOfTerritories && this->mapName == map.mapName;
}

/**
 * vector containing list of player territories
 */
std::vector<Territory*> Map::getTerritoriesByPlayer(Player *player) {
    std::vector<Territory*> territoriesByPlayer;
    for (Territory* territory: this->listOfTerritories){
        if (territory->getOwner() == player)
            territoriesByPlayer.push_back(territory);
    }
    return territoriesByPlayer;
}

//*********************************** MAP LOADER *****************************************

/**
 * Default Constructor
 */
MapLoader::MapLoader()
{
    this->mapFileName = nullptr;
}

/**
 * Copy Constructor makes a copy of Map Loader.
 * @param map Map
 */
MapLoader::MapLoader(MapLoader& map)
{
    mapFileName = map.mapFileName;
}

/**
 * Assignment Operator
 * @param map Map
 */
MapLoader& MapLoader:: operator = (const MapLoader& map)
{
    return *this;
}

/**
 * Destructor
 * Destroys the maps file name.
 */
MapLoader::~MapLoader()
{
}

/**
 * Parameterized constructor
 * @param mapFileName Name of the file that will be read to construct the map.
 */
MapLoader::MapLoader(std::string mapFileName)
{
    this->mapFileName = mapFileName;
}

/**
 * Reads map file to construct the map to be played with.
 * @param map Map Object.
 * @param filename Name of map file that will be played with.
 * @return Map Object.
 */
void MapLoader::readMap(Map* map)
{
    Continent* newContinent;
    Territory* newTerritory;
    std::string line = "";
    bool hasContinent = false;
    bool hasTerritory = false;
    bool hasAdj = false;

    std::ifstream inStream;
    inStream.open(mapFileName);

    if (inStream.fail())
        throw std::runtime_error("Unable to open file");
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
                    if (line.empty() or line == "\r" or line.starts_with(';'))
                        break;

                    //Split line to access different attributes of continents
                    std::vector<std::string> attributes = splitString(line);
                    newContinent = new Continent(index /*stores continent id*/, attributes[0]/*stores continent name*/, stoi(attributes[1])/*stores army value as an integer*/);
                    map->addContinent(newContinent);
                    std::cout << "New Continent: " << index << " " << attributes[0] << " " << attributes[1] << std::endl;
                    index++;
                    getline(inStream, line);
                }

                std::cout << std::endl;
                hasContinent = true;
            }

            if (line.find("[countries]") == 0 && hasContinent)
            {
                getline(inStream, line);

                while (line.find("[borders]") != 0)
                {
                    if (line.empty() or line == "\r" or line.starts_with(';'))
                        break;

                    std::vector<std::string> attributes = splitString(line);
                    newTerritory = new Territory(stoi(attributes[0])/*stores territory id as an integer*/, attributes[1] /*stores territory name*/, stoi(attributes[2])/*stores the continent id the territory belongs to as an integer*/);
                    map->listOfContinents[stoi(attributes[2]) - 1]->addTerritory(newTerritory); //adds the territory to a continent.
                    map->addTerritory(newTerritory); //adds the territory to list of all territories.

                    std::cout << "New Territory: " << attributes[0] << " " << attributes[1] << " " << attributes[2] << std::endl;
                    getline(inStream, line);
                }

                hasTerritory = true;
            }

            if (line.find("[borders]") == 0 && hasContinent && hasTerritory)
            {
                getline(inStream, line);
                while (!line.empty())
                {
                    if (line.empty() or line == "\r" or line.starts_with(';'))
                        break;

                    std::vector<std::string> adjTerritories = splitString(line);
                    Territory* t1 = map->getTerritory(stoi(adjTerritories[0]));
                    std::cout << "\nNew Border: " << adjTerritories[0];
                    for (int i = 1; i < adjTerritories.size(); i++)
                    {
                        Territory* t2 = map->getTerritory(stoi(adjTerritories[i]));
                        map->addAdjTerritory(t1, t2);

                        std::cout << " " << adjTerritories[i];
                    }


                    getline(inStream, line);
                }

                hasAdj = true;
            }
        }

        if (hasContinent && hasTerritory && hasAdj)
        {
            // Map is valid
            inStream.close();
        }
        else
        {
            // Map is invalid
            inStream.close();
            throw std::runtime_error("Map is invalid");
        }
    }
}

/**
 * Split string read from the map file.
 */
std::vector<std::string> MapLoader::splitString(std::string s)
{
    std::istringstream iss(s);
    std::vector<std::string> v;
    while (iss >> s)
    {
        v.push_back(s);
    }
    return v;
}

/**
 * Output Stream for Map Loader.
 */
std::ostream& operator << (std::ostream& o, const MapLoader& ml)
{
    return o << "This is a domination map: " << ml.mapFileName;
}
