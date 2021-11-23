#include <iostream>
#include "../core/Map.h"

int main()
{
    std::string mapName;
    bool isValid = false;
    do
    {
        std::cout << "Enter the name of the map file you wish to play with: ";
        std::cin >> mapName;
        std::cout << "\nMap details: \n\n";
        auto* map = new Map(mapName);
        auto* mapLoader = new MapLoader(mapName);
        try {
            mapLoader->readMap(map);
            if (map->validate())
                isValid = true;

            std::cout << "\nTotal Number of Continents: " << map->listOfContinents.size() << std::endl;
            std::cout << "Total Number of Territories: " << map->listOfTerritories.size() << std::endl;
            auto* terr1 = map->getTerritory(1);
            terr1->printAdjTerritory();
        } catch (std::runtime_error&) {
            std::cerr << "Invalid Map File" << std::endl;
        }
    } while (!isValid);
}