#include <iostream>
#include "../core/CommandProcessing.h"

int main(){
    GameEngine gameEngine;
    auto* commandProcessor = new CommandProcessor(gameEngine);
    Command* command = commandProcessor->getCommand();
    std::cout << *command << std::endl;

    auto* fileCommandProcessor = new FileCommandProcessorAdapter(gameEngine, "../commands.txt");
    Command* fileCommand = fileCommandProcessor->getCommand();
    std::cout << *fileCommand << std::endl;
}