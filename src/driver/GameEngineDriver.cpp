#include <iostream>
#include "../core/GameEngine.h"
using namespace std;


void gameEngineDriver() {
    GameEngine gameEngine = GameEngine();
    auto* logObserver = new LogObserver(&gameEngine);
    cout << "==========================" << endl;
    cout << "Welcome to Warzone" << endl;
    cout << "==========================" << endl;
    gameEngine.startupPhase(gameEngine);
    gameEngine.Detach(logObserver);
}