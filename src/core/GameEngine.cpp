#include <iostream>
#include <random>
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Orders.h"

const boost::unordered_map<std::string, GameEngine::GameCommand> GameEngine::gameCommandMapping = boost::assign::map_list_of("loadmap", GameEngine::GameCommand::load_map)
        ("validatemap", GameEngine::GameCommand::validate_map) ("addplayer", GameEngine::GameCommand::add_player) ("gamestart", GameEngine::GameCommand::game_start)
        ("issueorder", GameEngine::GameCommand::issue_order) ("issueorderend", GameEngine::GameCommand::end_issue_order) ("executeorder", GameEngine::GameCommand::execute_order)
        ("endexecuteorder", GameEngine::GameCommand::end_execute_order) ("win", GameEngine::GameCommand::win_game) ("replay", GameEngine::GameCommand::replay) ("quit", GameEngine::GameCommand::quit);

const boost::unordered_map<std::string, GameEngine::GameState> GameEngine::gameStateMapping = boost::assign::map_list_of("start", GameEngine::GameState::start)
        ("map loaded", GameEngine::GameState::map_loaded) ("map validated", GameEngine::GameState::map_validated) ("players added", GameEngine::GameState::players_added) ("assign reinforcement", GameEngine::GameState::assign_reinforcement)
        ("issue orders", GameEngine::GameState::issue_orders) ("execute orders", GameEngine::GameState::execute_orders) ("start", GameEngine::GameState::start) ("win", GameEngine::GameState::win);

/**
 * Game Engine constructor
 */
GameEngine::GameEngine()
{
    this->current_state = new GameState(GameState::start);
    this->map = new Map();
    this->players = vector<Player*>();
    this->deck = new Deck();
}

/**
 * Game Engine copy constructor
 * @param gameEngine Game Engine to copy
 */
GameEngine::GameEngine(const GameEngine &gameEngine)
{
    this->current_state = new GameState(*gameEngine.current_state);
    this->map = new Map(*gameEngine.map);
    this->deck = new Deck(*gameEngine.deck);
    this->players = vector<Player*>();
    for (Player* player: gameEngine.players)
        this->players.push_back(new Player(*player));
}

/**
 * Game Engine assignment operator
 * @param gameEngine Game engine to copy
 * @return Newly copied game engine
 */
GameEngine& GameEngine::operator=(const GameEngine &gameEngine)
{
    if (this != &gameEngine){
        // Copy players
        for (Player* player: this->players)
            delete player;
        this->players = std::vector<Player*>();
        for (Player* player: gameEngine.players)
            this->players.push_back(new Player(*player));

        // Copy game-state
        delete this->current_state;
        this->current_state = new GameState(*gameEngine.current_state);

        // Copy map
        delete this->map;
        this->map = new Map(*gameEngine.map);

        // Copy deck
        for (Card* card: this->deck->getCards())
            delete card;

        // Copy deck
        auto* newCards = new std::vector<Card*>();
        for (Card* card: gameEngine.deck->getCards())
            newCards->push_back(new Card(*card));
        this->deck->setCards(*newCards);
    }
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
vector<Player*> &GameEngine::getPlayers() {
    return players;
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
void GameEngine::transition(Command* command)
{
    std::string effect;
    bool foundCommand = false;
    std::vector<GameCommand> commands;
    getAvailableCommands(commands);
    for (GameCommand gameCommand: commands){
        if (gameCommand == *command->getGameCommand()) {
            foundCommand = true;
            // Perform move
            switch (gameCommand){
                case load_map:
                    try {
                        this->loadMap(command->getParam());
                        effect = "Map loaded";
                        std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
                        *current_state = map_loaded;
                    } catch (std::runtime_error&) {
                        effect = "Could not load map. Try again.";
                        std::cout << endl << "\x1B[31m" << effect << "\033[0m" << endl << endl;
                    }
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case validate_map:
                    if (map != nullptr && map->validate()) {
                        this->validateMap();
                        effect = "Map validated";
                        std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
                        *current_state = map_validated;
                    }
                    else {
                        map->~Map();
                        effect = "Invalid Map File";
                        std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
                        *current_state = start;
                    }
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case add_player:
                    this->addPlayer(command);
                    *current_state = players_added;
                    notify(this);
                    break;
                case game_start:
                    if (players.size() < 2) {
                        effect = "Insufficient number of players. Please add more players.";
                        std::cout << std::endl << "\x1B[31m" << effect << "\033[0m" << std::endl << std::endl;
                    }
                    else {
                        this->gameStart();
                        effect = "Game started. Proceed to 'play' phase.";
                        std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
                        *current_state = assign_reinforcement;
                    }
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case issue_order:
                    std::cout << std::endl << "\x1B[32m" << "Issue orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = issue_orders;
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case end_issue_order:
                    std::cout << std::endl << "\x1B[32m" << "End issue orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = execute_orders;
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case execute_order:
                    std::cout << std::endl << "\x1B[32m" << "Execute orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = execute_orders;
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case end_execute_order:
                    std::cout << std::endl << "\x1B[32m" << "End execute orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = assign_reinforcement;
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case win_game:
                    std::cout << std::endl << "\x1B[32m" << "Win game" << "\033[0m" << std::endl << std::endl;
                    *current_state = win;
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case replay:
                    effect = "Game restarted";
                    std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
                    *current_state = start;
                    command->saveEffect(effect);
                    notify(this);
                    break;
                case quit:
                    effect = "Exiting game";
                    std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
                    command->saveEffect(effect);
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
void GameEngine::startupPhase(CommandProcessor* commandProcessor)
{
    std::cout << std::endl << "*Startup Phase*" << std::endl << std::endl;
    printAvailableCommands();
    auto* command = commandProcessor->getCommand();
    attachExistingObservers(command);
    transition(command);
    while (*(this->current_state) != assign_reinforcement) {
        printAvailableCommands();
        transition(commandProcessor->getCommand());
    }
}

/**
 * Assign armies to reinforcement pool
 */
void GameEngine::reinforcementPhase()
{

    cout << "*Reinforcement Phase*" << endl << endl;

    for(Player* player: this->players) {
        int size_TerritoriesByPlayer = map->getTerritoriesByPlayer(player).size();
        if (size_TerritoriesByPlayer < 3) {    //size of territories less than 3
            player->armyPool += 3;              //default 3 armies
            cout << player->getName() << " gets default 3 armies." << endl;
        }
        else {
            int armiesToGive = size_TerritoriesByPlayer / 3;
            player->armyPool += armiesToGive;
            cout << player->getName() << " gets default " << armiesToGive << " armies." << endl;
        }
        for(Continent *continent : this->map->listOfContinents) {
            if (continent->isOwnedByPlayer(player)) {           //if player owns all territories of continent
                int continentBonusValue = continent->getArmyValue();
                player->armyPool += continentBonusValue;
                cout << player->getName() << " gets additional " << continentBonusValue << " armies as continent bonus for owning the entirety of " << continent->getContName() << endl;
            }
        }
        cout << player->getName() << " can deploy a total of " << player->armyPool << " troops." << endl << endl;
    }
    transition(new Command(GameEngine::GameCommand::issue_order)); // change state to issue order
}

/**
 * For each player, issue order. Call to issueOrder()
 */
void GameEngine::issueOrdersPhase()
{
    for (Player* player : this->players) {
        cout << player->getName() << "'s Turn!" << endl << endl;
        player->issueOrder(deck,map,players);
    }
    transition(new Command(GameEngine::GameCommand::end_issue_order)); // change state to end issue order
}

/**
 * Executes the order. Removes order from orderlist
 */
void GameEngine::executeOrdersPhase()
{
    cout << "*Execution Phase*" << endl << endl;

    std::map<Player*, bool> playerHasOrdersToExecute;
    for(Player* player: this->players) {
        playerHasOrdersToExecute[player] = true;   //orderList has content
    }
    while(containsOrders(playerHasOrdersToExecute)) { // continue while there are still orders to execute
        for (Player *player: this->players) { // Round-robin fashion for each player
            if (player->orderList->getSize() > 0) {
                player->orderList->getOrders().at(0)->execute(); //execute order;
                player->orderList->remove(0);
            } else
                playerHasOrdersToExecute[player] = false;
        }
    }
    transition(new Command(GameEngine::GameCommand::end_execute_order)); // change state to end execute order
}

/**
 * Main Game Loop containing 3 phases: Reinforcement Phase, Issue Orders Phase, and execute Orders Phase
 * Loop continues until one of the players owns all territories in map. If player does
 * not control at least one territory, player is removed from game
 *
 */
void GameEngine::mainGameLoop(CommandProcessor* commandProcessor)
{
    startupPhase(commandProcessor);
    bool playing = true;
    while(playing){
        bool allcontinents;
        for(Player* player: this->players) {
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

/**
 * uses hash map to determine if player has orders
 * @param playerHasOrdersToExecute hash map of player and boolean value
 * @return true if player has orders, else false
 */
bool GameEngine::containsOrders(const std::map<Player*, bool>& playerHasOrdersToExecute) {
    for (auto & it : playerHasOrdersToExecute) {
        if(it.second)
            return true;    //there is a true value
    }
    return false;
}

/**
 * load map
 * @param mapName string
 */
void GameEngine::loadMap(const std::string& mapName)
{
    this->map->setMapName(mapName);
    auto mapLoader = MapLoader(mapName);
    mapLoader.readMap(map);
}

/**
 * Validate map
 */
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

/**
 * Add players to the game (2 to 6 players allowed)
 * @param playerName string
 */
void GameEngine::addPlayer(Command* command)
{
    std::string effect;
    if (players.size() == 6) {
        effect = "Maximum number of players reached";
        std::cout << std::endl << "\x1B[31m" << effect << "\033[0m" << std::endl << std::endl;
    }
    else {
        bool found = false;
        for (Player* player: this->players){
            if (player->getName() == command->getParam()) {
                effect = "Player (" + command->getParam() + ") already exist";
                std::cout << std::endl << "\x1B[31m" << effect << "\033[0m" << std::endl << std::endl;
                found = true;
            }
        }
        if (!found) {
            effect = "Player (" + command->getParam() + ") added";
            std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
            auto* player = new Player(command->getParam());
            attachExistingObservers(player->orderList);
            this->players.push_back(player);
        }
    }
    command->saveEffect(effect);
}

/**
 * remove player from game
 * @param player name string
 */
void GameEngine::removePlayer(const std::string &playerName) {
    int count=0;
    for(Player* player: this->players){
        if(player->getName() == playerName){
            players.erase(players.begin() + count);
            break;
        }
        count++;
    }
}

/**
 * Fairly distribute all territories to the players
 * Determine order of play of players
 * Initialize 50 armies to reinforcement pool to each player
 * Draw 2 cards
 * switch the game to play phase
 */
void GameEngine::gameStart()
{
    // Create deck for this game
    deck = new Deck();

    // Randomize player order
    std::shuffle(players.begin(), players.end(), std::random_device {});

    // Randomize territories
    std::shuffle(map->listOfTerritories.begin(), map->listOfTerritories.end(), std::random_device {});

    // Print order of play
    std::cout << endl << "The order of play will be: " << endl;

    // Keep track of territories handed out
    int terrCounter = 0;

    for (auto* player : players) {
        // Assign territories sequentially
        for (int j = 0; j < (map->listOfTerritories.size() / players.size()); j++) {
            map->listOfTerritories[terrCounter]->setOwner(player);
            terrCounter++;
        }
        // Add armies to reinforcement pool
        player->armyPool = 50;

        // Draw 2 cards
        player->hand->addCard(deck->draw());
        player->hand->addCard(deck->draw());

        // Print player to show order
        cout << *player;
    }
}
/**
 * Prints available commands
 */
void GameEngine::printAvailableCommands(){
    cout << "Available commands:" << endl;
    vector<GameEngine::GameCommand> commands;
    getAvailableCommands(commands);
    int counter = 1;
    for (GameEngine::GameCommand command: commands){
        cout << counter++ << ". " << command << endl;
    }
}
/**
 * Game state to string
 * @return currentState of game
 */
std::string GameEngine::stringToLog() {
    std::string currentState = std::to_string(this->getGameState());
    std::string strGameState;
    for (auto& it: GameEngine::gameStateMapping){
        if (it.second == *this->current_state)
            strGameState = it.first;
    }
    return "Game Engine new state: " + strGameState;
}

void GameEngine::attachExistingObservers(Subject *subject) {
    for (Observer* observer: this->getObservers())
        subject->attach(observer);
}
