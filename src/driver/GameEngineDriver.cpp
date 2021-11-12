#include <iostream>
#include "../core/GameEngine.h"
#include "../core/CommandProcessing.h"

int main() {
    GameEngine gameEngine;
    cout << "==========================" << endl;
    cout << "Welcome to Warzone" << endl;
    cout << "==========================" << endl;
    gameEngine.startupPhase(new CommandProcessor(gameEngine));
}