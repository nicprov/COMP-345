#include "Map.h"
#include <iostream>
#include <string>
#include <any>

using namespace std;

int main()
{
	//Read map file
	string mapName;

	bool isValid = false;
	Map* map = nullptr;
	do
	{
		cout << "Enter the name of the map file you wish to play with: \n";
		cin >> mapName;

		cout << "\nMap details: \n\n";
		Map* map = new Map(mapName);
		MapLoader* mapLoader = new MapLoader(mapName);
		map = mapLoader->GetMap(map, mapName);

		map->validate();

		cout << "\nTotal Number of Continents: " << map->listOfContinents.size() << endl;
		cout << "Total Number of Territories: " << map->listOfTerritories.size() << endl;
		
		Territory* terr1 = map->getTerritory(1);

		terr1->printAdjTerritory();
		
		exit(0);
	} while (map == NULL || !isValid);

}