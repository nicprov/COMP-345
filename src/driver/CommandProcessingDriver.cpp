#include "../core/CommandProcessing.h"

void commandProcessingDriver(CommandProcessor* commandProcessor){
    GameEngine gameEngine;
    while (true)
        commandProcessor->getCommand();
//    auto* fileCommandProcessorAdapter = new FileCommandProcessorAdapter(gameEngine, "../commands.txt");
//    fileCommandProcessorAdapter->getCommand();
//    fileCommandProcessorAdapter->getCommand();
//    fileCommandProcessorAdapter->getCommand();
}