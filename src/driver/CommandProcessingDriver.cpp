#include <iostream>
#include "../core/CommandProcessing.h"

int main(){
    GameEngine gameEngine;
    auto* commandProcessor = new CommandProcessor(gameEngine);
    auto* command = commandProcessor->getCommand();
    std::cout << *command << std::endl;

    auto* fileCommandProcessor = new FileCommandProcessorAdapter(gameEngine, "../commands.txt");
    auto* fileCommand = fileCommandProcessor->getCommand();
    std::cout << *fileCommand << std::endl;
}