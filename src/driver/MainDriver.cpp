#include "../core/GameEngine.h"
#include "../core/CommandProcessing.h"

int main(int argc, char *argv[]){
    const std::string logFile = "../log/gamelog.txt";
    auto* logObserver = new LogObserver(logFile);
    GameEngine gameEngine;
    CommandProcessor* commandProcessor;
    switch (argc) {
        case 2:
            if (strcmp(argv[1], "-console") == 0){
                commandProcessor = new CommandProcessor(gameEngine);
            } else
                throw std::runtime_error("Must include either -console or -file <filename> when launching program");
            break;
        case 3:
            if (strcmp(argv[1], "-file") == 0){
                commandProcessor = new FileCommandProcessorAdapter(gameEngine, argv[2]);
            } else
                throw std::runtime_error("Must include either -console or -file <filename> when launching program");
            break;
        default:
            throw std::runtime_error("Must include either -console or -file <filename> when launching program");
    }
    gameEngine.attach(logObserver);
    commandProcessor->attach(logObserver);
    gameEngine.startupPhase(commandProcessor);
}