#include <string>
#include "CardsDriver.cpp"
#include "GameEngineDriver.cpp"
#include "OrdersDriver.cpp"
#include "PlayerDriver.cpp"
#include "MapDriver.cpp"
#include "CommandProcessingDriver.cpp"

int main(int argc, char *argv[]){
    GameEngine* gameEngine = new GameEngine();
    /*CommandProcessor* commandProcessor;
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
*/
//    cout << "Running Map Driver" << endl;
//    cout << "-----------------------" << endl;
//    mapDriver();
//    cout << endl << endl << "Running Player Driver" << endl;
//    cout << "-----------------------" << endl;
//    PlayerDriver();
//    cout << endl << endl << "Running Orders Driver" << endl;
//    cout << "-----------------------" << endl;
//    ordersDriver();
//    cout << endl << endl << "Running Cards Driver" << endl;
//    cout << "-----------------------" << endl;
//    cardsDriver();
//    cout << endl << endl << "Running Game Engine Driver" << endl;
//    cout << "-----------------------" << endl;
    gameEngineDriver();
//    commandProcessingDriver(commandProcessor);
}