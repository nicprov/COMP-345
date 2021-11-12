#include <iostream>
#include <random>
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Orders.h"

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
    this->map = new Map();
    this->players = new vector<Player*>();
    this->deck = new Deck();
}

/**
 * Game Engine copy constructor
 * @param gameEngine Game Engine to copy
 */
GameEngine::GameEngine(const GameEngine &gameEngine)
{
    this->current_state = new GameState(*gameEngine.current_state);
    this->players = new vector<Player*> (*gameEngine.players);
    this->map = new Map(*gameEngine.map);
    this->deck = new Deck(*gameEngine.deck);
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
 * Get list of current players in the game
 * @return list of players
 */
vector<Player *> &GameEngine::getPlayers() {
    return *players;
}

/**
 * Get current map in the game
 * @return current map
 */
Map &GameEngine::getMap() {
    return *map;
}

/**
 * Get current deck in the game
 * @return current deck
 */
Deck &GameEngine::getDeck() {
    return *deck;
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
void GameEngine::transition(GameCommand &gameCommand, const std::string& param)
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
                    try {
                        this->loadMap(param);
                        std::cout << std::endl << "\x1B[32m" << "Map loaded" << "\033[0m" << std::endl << std::endl;
                        *current_state = map_loaded;
                    } catch (std::runtime_error&) {
                        std::cout << endl << "\x1B[31m" << "Could not load map. Try again." << "\033[0m" << endl << endl;
                    }
                    Notify(this);
                    break;
                case validate_map:
                    if (map != nullptr && map->validate()) {
                        this->validateMap();
                        std::cout << std::endl << "\x1B[32m" << "Map validated" << "\033[0m" << std::endl << std::endl;
                        *current_state = map_validated;
                        Notify(this);
                    }
                    else {
                        map->~Map();
                        cerr << "Invalid Map File.";
                        *current_state = start;
                    }
                    break;
                case add_player:
                    this->addPlayer(param);
                    *current_state = players_added;
                    Notify(this);
                    break;
                case game_start:
                    if (players->size() < 2)
                        std::cout << std::endl << "\x1B[31m" << "Insufficient number of players. Please add more players." << "\033[0m" << std::endl << std::endl;
                    else {
                        this->gameStart();
                        std::cout << std::endl << "\x1B[32m" << "Game started. Proceed to 'play' phase." << "\033[0m" << std::endl << std::endl;
                        *current_state = assign_reinforcement;
                    }
                    Notify(this);
                    break;
                case issue_order:
                    std::cout << std::endl << "\x1B[32m" << "Issue orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = issue_orders;
                    Notify(this);
                    break;
                case end_issue_order:
                    std::cout << std::endl << "\x1B[32m" << "End issue orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = execute_orders;
                    Notify(this);
                    break;
                case execute_order:
                    std::cout << std::endl << "\x1B[32m" << "Execute orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = execute_orders;
                    Notify(this);
                    break;
                case end_execute_order:
                    std::cout << std::endl << "\x1B[32m" << "End execute orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = assign_reinforcement;
                    Notify(this);
                    break;
                case win_game:
                    std::cout << std::endl << "\x1B[32m" << "Win game" << "\033[0m" << std::endl << std::endl;
                    *current_state = win;
                    Notify(this);
                    break;
                case replay:
                    std::cout << std::endl << "\x1B[32m" << "Play game" << "\033[0m" << std::endl << std::endl;
                    *current_state = start;
                    Notify(this);
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
            stream << "Load Map (loadmap <fileName>)";
            break;
        case GameEngine::GameCommand::validate_map:
            stream << "Validate Map (validatemap)";
            break;
        case GameEngine::GameCommand::add_player:
            stream << "Add player (addplayer <playerName>)";
            break;
        case GameEngine::GameCommand::game_start:
            stream << "Game start (gamestart)";
            break;
        case GameEngine::GameCommand::issue_order:
            stream << "Issue order (issueorder)";
            break;
        case GameEngine::GameCommand::end_issue_order:
            stream << "End issue order (issueordersend)";
            break;
        case GameEngine::GameCommand::execute_order:
            stream << "Execute order (executeorder)";
            break;
        case GameEngine::GameCommand::end_execute_order:
            stream << "End execute order (endexecuteorders)";
            break;
        case GameEngine::GameCommand::win_game:
            stream << "Win game (win)";
            break;
        case GameEngine::GameCommand::replay:
            stream << "Replay game (replay)";
            break;
        case GameEngine::GameCommand::quit:
            stream << "Quit (quit)";
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
    CommandProcessor* commandProcessor = new CommandProcessor(gameEngine);
    std::cout << std::endl << "*Startup Phase*" << std::endl << std::endl;
    printAvailableCommands(gameEngine);
    Command* command = commandProcessor->getCommand();    
    gameEngine.transition(*command->getGameCommand(), command->getParam());
    while (*(gameEngine.current_state) != assign_reinforcement) {
        printAvailableCommands(gameEngine);
        command = commandProcessor->getCommand();
        gameEngine.transition(*command->getGameCommand(), command->getParam());
    }
}

void GameEngine::reinforcementPhase()
{
    for(Player* player: *this->players) {
        for(Continent *continent : this->map->listOfContinents) {
            if (continent->isOwnedByPlayer(player)) {           //if player owns all territories of continent
                int continentBonusValue = continent->getArmyValue();
                player->armyPool += continentBonusValue;
                cout << player->getName() << "gets additional " << continentBonusValue << " armies as continent bonus." << endl;
            } else {                                            // player does not own all territories of continent
                int size_TerritoriesByPlayer = map->getTerritoriesByPlayer(player).size();
                if(size_TerritoriesByPlayer < 3) {    //size of territories less than 3
                    player->armyPool += 3;              //default 3 armies
                    cout << player->getName() << "gets default 3 armies." << endl;
                } else {
                    int armiesToGive = size_TerritoriesByPlayer / 3;
                    player->armyPool += armiesToGive;
                    cout << player->getName() << "gets default " << armiesToGive << " armies." << endl;
                }
            }
        }
    }
}


void GameEngine::issueOrdersPhase()
{
    for(Player* player: *this->players) {
        Order *order = nullptr;
        while (order == nullptr) {
            for (Order::OrderType orderType: Order::ALL_ORDER_TYPES) {
                std::cout << static_cast<int>(orderType) << ": " << orderType << std::endl;
            }
            std::cout << "Choice: ";
            int orderType;
            std::cin >> orderType;
            switch (orderType) {
                case 1:
                    order = new Deploy(Order::OrderType::deploy);
                    player->orderList->add(order);
                    break;
                case 2:
                    order = new Advance(Order::OrderType::advance);
                    player->orderList->add(order);
                    break;
                case 3:
                    order = new Bomb(Order::OrderType::bomb);
                    player->orderList->add(order);
                    break;
                case 4:
                    order = new Blockade(Order::OrderType::blockade);
                    player->orderList->add(order);
                    break;
                case 5:
                    order = new Airlift(Order::OrderType::airlift);
                    player->orderList->add(order);
                    break;
                case 6:
                    order = new Negotiate(Order::OrderType::negotiate);
                    player->orderList->add(order);
                    break;
                default:
                    std::cout << "Invalid choice";
                    order = nullptr;//**TO DO: LOOP BACK IF INVALID ORDER CHOICE
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
    bool playing = true;
    while(playing){
        bool allcontinents;
        for(Player* player: *this->players) {
            allcontinents = true;
            for(Continent* continent: map->listOfContinents){
                if(!continent->isOwnedByPlayer(player)){
                    allcontinents = false;
                }
            }
            if(map->getTerritoriesByPlayer(player).empty()){
                removePlayer(player->getName());
            }
        }
        if(allcontinents){
            playing = false;
        }
        else{
            reinforcementPhase();
            issueOrdersPhase();
            executeOrdersPhase();
        }
    }
}

bool GameEngine::containsOrders(std::map<Player*, bool> map) {
    for (auto it = map.begin(); it != map.end(); ++it) {
        if(it->second)
            return true;    //there is a true value
    }
    return false;
}
void GameEngine::loadMap(const std::string& mapName)
{
    this->map->setMapName(mapName);
    auto mapLoader = MapLoader(mapName);
    mapLoader.readMap(map);
}

void GameEngine::validateMap()
{
    if (map != nullptr && map->validate()) {
        std::cout << "\nTotal Number of Continents: " << map->listOfContinents.size() << endl;
        std::cout << "Total Number of Territories: " << map->listOfTerritories.size() << endl;
    }
    else {
        std::cout << std::endl << "\x1B[31m" << "Invalid Map File. Try loading a different map!" << "\033[0m" << std::endl << std::endl;
    }
}

void GameEngine::addPlayer(const std::string& playerName)
{
    if (players->size() == 6)
        std::cout << std::endl << "\x1B[31m" << "Maximum number of players reached." << "\033[0m" << std::endl << std::endl;
    else {
        bool found = false;
        for (Player* player: *this->players){
            if (player->getName() == playerName) {
                std::cout << std::endl << "\x1B[31m" << "Player (" << playerName << ") already exist" << "\033[0m" << std::endl << std::endl;
                found = true;
            }
        }
        if (!found) {
            this->players->push_back(new Player(playerName));
            std::cout << std::endl << "\x1B[32m" << "Players added" << "\033[0m" << std::endl << std::endl;
        }
    }
}
void GameEngine::removePlayer(const std::string &playerName) {
    int count=0;
    for(Player* player: *this->players){
        if(player->getName() == playerName){
            players->erase(players->begin()+count);
            break;
        }
        count++;
    }
}

void GameEngine::gameStart()
{
    //Create deck for this game
    deck = new Deck();

    //Assign territories, armies and draw card sequentially
    auto nbTerr = map->listOfTerritories.size();
    auto nbPlayers = players->size();
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

    //Print order of play
    std::cout << endl << "The order of play will be: " << endl;

    for (const auto* value : *players) {
        cout << *value << endl;
    }
}

void GameEngine::printAvailableCommands(GameEngine &gameEngine){
    cout << "Available commands:" << endl;
    vector<GameEngine::GameCommand> commands;
    gameEngine.getAvailableCommands(commands);
    int counter = 1;
    for (GameEngine::GameCommand command: commands){
        cout << counter++ << ". " << command << endl;
    }
}

std::string GameEngine::stringToLog() {
    std::string currentState = std::to_string(this->getGameState());
    return "Game Engine with State: " + currentState;
}
