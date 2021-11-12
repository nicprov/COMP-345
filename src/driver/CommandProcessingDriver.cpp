#include "../core/CommandProcessing.h"

void commandProcessingDriver(CommandProcessor* commandProcessor){
    GameEngine gameEngine;
    LogObserver* cp = new LogObserver(commandProcessor);
    while (true)
        commandProcessor->getCommand();
//    auto* fileCommandProcessorAdapter = new FileCommandProcessorAdapter(gameEngine, "../commands.txt");
//    fileCommandProcessorAdapter->getCommand();
//    fileCommandProcessorAdapter->getCommand();
//    fileCommandProcessorAdapter->getCommand();
    commandProcessor->Detach(cp);
}