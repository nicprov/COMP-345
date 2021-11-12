#include <iostream>
#include "../core/Map.h"

int main()
{
    string mapName;
    bool isValid = false;
    do
    {
        cout << "Enter the name of the map file you wish to play with: ";
        cin >> mapName;
        cout << "\nMap details: \n\n";
        Map* map = new Map(mapName);
        auto* mapLoader = new MapLoader(mapName);
        try {
            mapLoader->readMap(map);
            if (map->validate())
                isValid = true;

            cout << "\nTotal Number of Continents: " << map->listOfContinents.size() << endl;
            cout << "Total Number of Territories: " << map->listOfTerritories.size() << endl;
            Territory* terr1 = map->getTerritory(1);
            terr1->printAdjTerritory();
        } catch (std::runtime_error&) {
            cerr << "Invalid Map File" << endl;
        }
    } while (!isValid);
}