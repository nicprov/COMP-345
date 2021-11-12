#include <iostream>
#include "../core/GameEngine.h"
using namespace std;


void gameEngineDriver() {
    GameEngine gameEngine = GameEngine();

    cout << "==========================" << endl;
    cout << "Welcome to Warzone" << endl;
    cout << "==========================" << endl;

    gameEngine.startupPhase(gameEngine);
    /*int choice = 0;
    while (choice != 11){
        listAvailableCommands(gameEngine);
        while(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\x1B[31m" << "Invalid input, try again: " << "\033[0m";
        }
        auto command = static_cast<GameEngine::GameCommand>(choice);
        gameEngine.transition(command);
    }*/
}