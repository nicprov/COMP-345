#include <string>
#include "CardsDriver.cpp"
#include "GameEngineDriver.cpp"
#include "OrdersDriver.cpp"
#include "PlayerDriver.cpp"
#include "MapDriver.cpp"
#include "CommandProcessingDriver.cpp"

int main(int argc, char *argv[]){

    GameEngine gameEngine;
    CommandProcessor* commandProcessor = new CommandProcessor(gameEngine);
    /*switch (argc) {
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
    }*/

    gameEngine.startupPhase(commandProcessor);
    gameEngine.mainGameLoop();
}