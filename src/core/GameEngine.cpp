#include <iostream>
#include <random>
#include "CommandProcessing.h"
#include "GameEngine.h"

const boost::unordered_map<std::string, GameEngine::GameCommand> GameEngine::gameCommandMapping = boost::assign::map_list_of("loadmap", GameEngine::GameCommand::load_map)
        ("validatemap", GameEngine::GameCommand::validate_map) ("addplayer", GameEngine::GameCommand::add_player) ("gamestart", GameEngine::GameCommand::game_start)
        ("issueorder", GameEngine::GameCommand::issue_order) ("issueorderend", GameEngine::GameCommand::end_issue_order) ("executeorder", GameEngine::GameCommand::execute_order)
        ("endexecuteorder", GameEngine::GameCommand::end_execute_order) ("win", GameEngine::GameCommand::win_game) ("replay", GameEngine::GameCommand::replay) ("quit", GameEngine::GameCommand::quit);

/**
 * Game Engine constructor
 */
GameEngine::GameEngine()
{
    this->current_state = new GameState(GameState::start);
}

/**
 * Game Engine copy constructor
 * @param gameEngine Game Engine to copy
 */
GameEngine::GameEngine(const GameEngine &gameEngine)
{
    this->current_state = new GameState(*gameEngine.current_state);
}

/**
 * Game Engine assignment operator
 * @param gameEngine Game engine to copy
 * @return Newly copied game engine
 */
GameEngine& GameEngine::operator=(const GameEngine &gameEngine)
{
    this->current_state = new GameState(*gameEngine.current_state);
    return *this;
}

/**
 * Get current game state
 * @return current game state
 */
GameEngine::GameState& GameEngine::getGameState()
{
    return *current_state;
}

/**
 * Get a list of available commands based on the current game state
 * @param availableCommands list of available commands to run
 */
void GameEngine::getAvailableCommands(std::vector<GameEngine::GameCommand> &availableCommands)
{
    switch (*current_state) {
        case start:
            availableCommands.push_back(GameCommand::load_map);
            break;
        case map_loaded:
            availableCommands.push_back(GameCommand::load_map);
            availableCommands.push_back(GameCommand::validate_map);
            break;
        case map_validated:
            availableCommands.push_back(GameCommand::add_player);
            break;
        case players_added:
            availableCommands.push_back(GameCommand::add_player);
            availableCommands.push_back(GameCommand::game_start);
            break;
        case assign_reinforcement:
            availableCommands.push_back(GameCommand::issue_order);
            break;
        case issue_orders:
            availableCommands.push_back(GameCommand::issue_order);
            availableCommands.push_back(GameCommand::end_issue_order);
            break;
        case execute_orders:
            availableCommands.push_back(GameCommand::execute_order);
            availableCommands.push_back(GameCommand::end_execute_order);
            availableCommands.push_back(GameCommand::win_game);
            break;
        case win:
            availableCommands.push_back(GameCommand::replay);
            availableCommands.push_back(GameCommand::quit);
            break;
    }
}

/**
 * Transition game state based on command
 * @param gameCommand Game command to run
 */
void GameEngine::transition(GameCommand &gameCommand)
{
    bool foundCommand = false;
    std::vector<GameCommand> commands;
    getAvailableCommands(commands);
    for (GameCommand gameCommand_: commands){
        if (gameCommand_ == gameCommand) {
            foundCommand = true;
            // Perform move
            switch (gameCommand){
                case load_map:
                    this->loadMap();
                    std::cout << std::endl << "\x1B[32m" << "Map loaded" << "\033[0m" << std::endl << std::endl;
                    *current_state = map_loaded;
                    break;
                case validate_map:
                    if (map != nullptr && map->validate()) {
                        this->validateMap();
                        std::cout << std::endl << "\x1B[32m" << "Map validated" << "\033[0m" << std::endl << std::endl;
                        *current_state = map_validated;
                    }
                    else {
                        map->~Map();
                        cerr << "Invalid Map File.";
                    }
                    break;
                case add_player:
                    this->addPlayers();
                    std::cout << std::endl << "\x1B[32m" << "Players added" << "\033[0m" << std::endl << std::endl;
                    *current_state = players_added;
                    break;
                case game_start:
                    this->gameStart();
                    std::cout << std::endl << "\x1B[32m" << "Assign reinforcement" << "\033[0m" << std::endl << std::endl;
                    *current_state = assign_reinforcement;
                    break;
                case issue_order:
                    std::cout << std::endl << "\x1B[32m" << "Issue orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = issue_orders;
                    break;
                case end_issue_order:
                    std::cout << std::endl << "\x1B[32m" << "End issue orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = execute_orders;
                    break;
                case execute_order:
                    std::cout << std::endl << "\x1B[32m" << "Execute orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = execute_orders;
                    break;
                case end_execute_order:
                    std::cout << std::endl << "\x1B[32m" << "End execute orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = assign_reinforcement;
                    break;
                case win_game:
                    std::cout << std::endl << "\x1B[32m" << "Win game" << "\033[0m" << std::endl << std::endl;
                    *current_state = win;
                    break;
                case replay:
                    std::cout << std::endl << "\x1B[32m" << "Play game" << "\033[0m" << std::endl << std::endl;
                    *current_state = start;
                    break;
                case quit:
                    std::cout << std::endl << "\x1B[32m" << "Exiting game" << "\033[0m" << std::endl << std::endl;
                    exit(0);
            }
        }
    }
    if (!foundCommand)
        std::cout << std::endl << "\x1B[31m" << "Invalid input" << "\033[0m" << std::endl << std::endl;
}

/**
 * Game Engine stream insertion operator
 * @param stream Output stream
 * @param gameEngine Game engine to print
 * @return Output stream
 */
std::ostream& operator<< (std::ostream &stream, const GameEngine &gameEngine)
{
    return stream << "Current state (" << gameEngine.current_state << ")";
}

/**
 * Game command stream insertion operator
 * @param stream Output stream
 * @param gameCommand Game command to print
 * @return Output stream
 */
std::ostream &operator<< (std::ostream &stream, const GameEngine::GameCommand &gameCommand)
{
    switch (gameCommand) {
        case GameEngine::GameCommand::load_map:
            stream << "Load Map";
            break;
        case GameEngine::GameCommand::validate_map:
            stream << "Validate Map";
            break;
        case GameEngine::GameCommand::add_player:
            stream << "Add player";
            break;
        case GameEngine::GameCommand::game_start:
            stream << "Assign countries";
            break;
        case GameEngine::GameCommand::issue_order:
            stream << "Issue order";
            break;
        case GameEngine::GameCommand::end_issue_order:
            stream << "End issue order";
            break;
        case GameEngine::GameCommand::execute_order:
            stream << "Execute order";
            break;
        case GameEngine::GameCommand::end_execute_order:
            stream << "End execute order";
            break;
        case GameEngine::GameCommand::win_game:
            stream << "Win game";
            break;
        case GameEngine::GameCommand::replay:
            stream << "Play game";
            break;
        case GameEngine::GameCommand::quit:
            stream << "End";
            break;
    }
    return stream;
}

/**
 * Compares game engine by looking at the current state
 * @param gameEngine Game engine to compare
 * @return True (if the game states match), False otherwise
 */
bool GameEngine::operator==(const GameEngine &gameEngine) const
{
    return *this->current_state == *gameEngine.current_state;
}
/**
* Startup phase of the game: goes through loadmap, validatemap,
* addplayer, gamestart through commands
* @param gameEngine with state 'start'
*/
void GameEngine::startupPhase(GameEngine& gameEngine)
{
    std::cout << std::endl << "*Startup Phase*" << std::endl << std::endl;

    int choice = 0;

    while (choice != 4) { // based on enum value in game engine getCommand()
        listAvailableCommands(gameEngine);
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\x1B[31m" << "Invalid input, try again: " << "\033[0m";
        }
        auto command = static_cast<GameEngine::GameCommand>(choice);
        gameEngine.transition(command);
    }
}

void GameEngine::reinforcementPhase()
{

}



void GameEngine::issueOrdersPhase()
{
    for(Player* player: *this->players) {
        Order *order = nullptr;

        while (order == nullptr) {
            for (Order::OrderType orderType: Order::ALL_ORDER_TYPES) {
                std::cout << static_cast<int>(orderType) << ": " << orderType;
            }
            std::cout << "Choice: ";
            int orderType;
            std::cin >> orderType;

            switch (orderType) {
                case 1:
                    order = new Deploy(Order::OrderType::deploy);
                    break;
                case 2:
                    order = new Advance(Order::OrderType::advance);
                    break;
                case 3:
                    order = new Bomb(Order::OrderType::bomb);
                    break;
                case 4:
                    order = new Blockade(Order::OrderType::blockade);
                    break;
                case 5:
                    order = new Airlift(Order::OrderType::airlift);
                    break;
                case 6:
                    order = new Negotiate(Order::OrderType::negotiate);
                    break;
                default:
                    cout << "Invalid choice";       //**TO DO: LOOP BACK IF INVALID ORDER CHOICE
                    break;
            }
        }

        player->issueOrder(order);
    }
}

void GameEngine::executeOrdersPhase()
{
    std::map<Player*, bool>listPlayerOrder;
    for(Player* player: *this->players) {
        listPlayerOrder[player] = true;   //orderList has content
    }
    while(containsOrders(listPlayerOrder)) {
        for (Player *player:*this->players) {
            if (player->orderList->getSize() > 0) {
                player->orderList->remove(0);
            }
        }
    }
}

void GameEngine::mainGameLoop()
{
    while(true){
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();
    }
    //for each state (execute orders, issue order, etc. )
    // for player in player
    // call method: ie. issueOrdersPhase(player reference)
}

void GameEngine::registerPlayer(Player* player) {
    this->players->push_back(player);
}

bool GameEngine::containsOrders(std::map<Player*, bool> map) {
    for (auto it = map.begin(); it != map.end(); ++it) {
        if(it->second)
            return true;    //there is a true value
    }
    return false;
}

void GameEngine::loadMap() {
    std::string name = "";
    MapLoader* mapLoader = new MapLoader();

    std::cout << "Enter the name of the map file you wish to play with: \n";
    std::cin >> name;
    this->map->setMapName(name);

    cout << "\nMap details: \n\n";
    this->map = mapLoader->GetMap(map, name);

    mapLoader->~MapLoader();

    std::cout << std::endl << "\x1B[32m" << "Map loaded" << "\033[0m" << std::endl << std::endl;
}

void GameEngine::validateMap() {

    if (map != nullptr && map->validate()) {

        cout << "\nTotal Number of Continents: " << map->listOfContinents.size() << endl;
        cout << "Total Number of Territories: " << map->listOfTerritories.size() << endl;

        /*Territory* terr1 = map->getTerritory(1);

        terr1->printAdjTerritory();*/

    }
    else {
        map->~Map();
        cerr << "Invalid Map File. Do load_map again!";
    }

}

void GameEngine::addPlayers() {
    int nbPlayers;

    while ((players->size() + nbPlayers) < 2 || (players->size() + nbPlayers) > 6) {
        cout << "Enter the number of players for this game (minimum 2, maximum 6): " << endl;
        while (!(cin >> nbPlayers)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\x1B[31m" << "Invalid input, try again: " << "\033[0m";
        }
    }
    for (int i = nbPlayers; i > 0; i--) {
        auto* playerName = new std::string();
        cout << "Enter player name: " << endl;
        cin >> *playerName;
        auto* player = new Player(*playerName);
        this->registerPlayer(player);
    }

}

void GameEngine::gameStart() {

    //Create deck for this game
    deck = new Deck();

    //Assign territories, armies and draw card sequentially
    int nbTerr = map->listOfTerritories.size();
    int nbPlayers = players->size();
    int terrCounter = 0;

    for (int i = 0; i < nbPlayers; i++) {
        //Assign territories sequentially
        for (int j = 0; j < (nbTerr / nbPlayers); j++) {
            map->listOfTerritories[terrCounter]->setOwner(this->players->at(i));
            terrCounter++;
        }
        //Add armies to reinforcement pool
        this->players->at(i)->armyPool = 50;

        //Draw 2 cards
        players->at(i)->hand->addCard(deck->draw());
        players->at(i)->hand->addCard(deck->draw());
    }

    //Randomize player order
    std::shuffle(players->begin(), players->end(), default_random_engine(0));
}

void GameEngine::listAvailableCommands(GameEngine &gameEngine){
    cout << "Available commands:" << endl;
    vector<GameEngine::GameCommand> commands;
    gameEngine.getAvailableCommands(commands);
    for (GameEngine::GameCommand command: commands){
        cout << static_cast<int>(command) << ". " << command << endl;
    }
    cout << "Choice: ";
}
//

