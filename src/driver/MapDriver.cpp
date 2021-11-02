#include <iostream>
#include <string>
#include "../core/Map.h"

void mapDriver()
{
	//Read map file
	string mapName;

	bool isValid = false;
	do
	{
		cout << "Enter the name of the map file you wish to play with: \n";
		cin >> mapName;

		cout << "\nMap details: \n\n";
		Map* map = new Map(mapName);
		MapLoader* mapLoader = new MapLoader(mapName);

        map = mapLoader->GetMap(map, mapName);
        if(map!= nullptr){
            if (map->validate())
                isValid = true;

            cout << "\nTotal Number of Continents: " << map->listOfContinents.size() << endl;
            cout << "Total Number of Territories: " << map->listOfTerritories.size() << endl;

            Territory* terr1 = map->getTerritory(1);

            terr1->printAdjTerritory();
        }
        else{
            cerr << "Invalid Map File";
        }



	} while (!isValid);

}