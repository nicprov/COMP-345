#include <iostream>
#include "../core/GameEngine.h"
#include "../core/CommandProcessing.h"

int main() {
    GameEngine gameEngine;
    std::cout << "==========================" << std::endl;
    std::cout << "Welcome to Warzone" << std::endl;
    std::cout << "==========================" << std::endl;
    gameEngine.mainGameLoop(new CommandProcessor(gameEngine));
}