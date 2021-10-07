#include <iostream>
#include "GameEngine.h"
using namespace std;

void listAvailableCommands(GameEngine &gameEngine){
    cout << "Available commands:" << endl;
    vector<GameEngine::Game_Command> commands;
    gameEngine.getAvailableCommands(commands);
    for (GameEngine::Game_Command command: commands){
        cout << static_cast<int>(command) << ". " << command << endl;
    }
    cout << "Choice: ";
}

int main() {
    GameEngine gameEngine = GameEngine();

    cout << "==========================" << endl;
    cout << "Welcome to Warzone" << endl;
    cout << "==========================" << endl;

    int choice = 0;
    while (choice != 11){
        listAvailableCommands(gameEngine);
        while(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\x1B[31m" << "Invalid input, try again: " << "\033[0m";
        }
        auto command = static_cast<GameEngine::Game_Command>(choice);
        gameEngine.transition(command);
    }
}