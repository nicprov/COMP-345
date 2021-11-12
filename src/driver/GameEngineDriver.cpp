#include <iostream>
#include "../core/GameEngine.h"

int main() {
    GameEngine gameEngine = GameEngine();
    cout << "==========================" << endl;
    cout << "Welcome to Warzone" << endl;
    cout << "==========================" << endl;
    gameEngine.mainGameLoop();
}