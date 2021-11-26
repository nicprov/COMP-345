#include <iostream>
#include <random>
#include <string>
#include <boost/algorithm/string.hpp>
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Orders.h"
#include "PlayerStrategies.h"

const boost::unordered_map<std::string, GameEngine::GameCommand> GameEngine::gameCommandMapping = boost::assign::map_list_of("loadmap", GameEngine::GameCommand::load_map)
        ("validatemap", GameEngine::GameCommand::validate_map) ("addplayer", GameEngine::GameCommand::add_player) ("gamestart", GameEngine::GameCommand::game_start)
        ("issueorder", GameEngine::GameCommand::issue_order) ("issueorderend", GameEngine::GameCommand::end_issue_order) ("executeorder", GameEngine::GameCommand::execute_order)
        ("endexecuteorder", GameEngine::GameCommand::end_execute_order) ("win", GameEngine::GameCommand::win_game) ("replay", GameEngine::GameCommand::replay) ("quit", GameEngine::GameCommand::quit)
        ("tournament", GameEngine::GameCommand::tournament);

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
    this->players = std::vector<Player*>();
    this->deck = new Deck();
    this->tournamentMode = false;
    this->numberOfGames = -1;
    this->gameCounter = 1;
    this->maxNumberOfTurns = -1;
    this->turnCounter = 0;
    this->toPrint = "";
    this->mapCounter = 0;
    this->tournamentResults = std::map<std::string, std::vector<std::string>>();
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
    this->players = std::vector<Player*>();
    this->tournamentMode = gameEngine.tournamentMode;
    this->numberOfGames = gameEngine.numberOfGames;
    this->gameCounter = gameEngine.gameCounter;
    this->maxNumberOfTurns = gameEngine.maxNumberOfTurns;
    this->turnCounter = gameEngine.turnCounter;
    this->toPrint = gameEngine.toPrint;
    this->mapCounter = gameEngine.mapCounter;
    this->tournamentResults = gameEngine.tournamentResults;
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
        this->tournamentMode = gameEngine.tournamentMode;
        this->numberOfGames = gameEngine.numberOfGames;
        this->gameCounter = gameEngine.gameCounter;
        this->maxNumberOfTurns = gameEngine.maxNumberOfTurns;
        this->turnCounter = gameEngine.turnCounter;
        this->toPrint = gameEngine.toPrint;
        this->mapCounter = gameEngine.mapCounter;
        this->tournamentResults = gameEngine.tournamentResults;
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
std::vector<Player*> &GameEngine::getPlayers() {
    return players;
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
            availableCommands.push_back(GameCommand::tournament);
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
                        this->loadMap(command->getParams()[0]);
                        effect = "Map loaded";
                        std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
                        *current_state = map_loaded;
                    } catch (std::runtime_error&) {
                        effect = "Could not load map. Try again.";
                        std::cout << std::endl << "\x1B[31m" << effect << "\033[0m" << std::endl << std::endl;
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
                        effect = "Game started.";
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
                    *current_state = end;
                    command->saveEffect(effect);
                    break;
                case tournament:
                    tournamentMode = true;
                    try {
                        validateTournamentParameters(command);
                        setupTournamentGame();
                        effect = "Tournament started";
                        std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
                    } catch (std::runtime_error& error) {
                        effect = "Invalid tournament parameters: ";
                        effect += error.what();
                        std::cout << std::endl << "\x1B[31m" << effect << "\033[0m" << std::endl << std::endl;
                    }
                    command->saveEffect(effect);
                    break;
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
            stream << "Add player (addplayer <playerName> <strategyType>)";
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
        case GameEngine::GameCommand::tournament:
            stream << "Tournament mode (tournament <listofmapfiles> <listofplayerstrategies> <numberofgames> <maxnumberofturns>)";
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
    while (*(this->current_state) != assign_reinforcement) {
        printAvailableCommands();
        auto* command = commandProcessor->getCommand();
        if (command != nullptr) {
            attachExistingObservers(command);
            transition(command);
        }
    }
}

/**
 * Assign armies to reinforcement pool
 */
void GameEngine::reinforcementPhase()
{
    std::cout << "*Reinforcement Phase*" << std::endl << std::endl;
    for(Player* player: this->players) {
        int numberTerritoriesByPlayer = this->map->getTerritoriesByPlayer(player).size();
        if (numberTerritoriesByPlayer < 3) {    //size of territories less than 3
            player->armyPool += 3;              //default 3 armies
            std::cout << player->getName() << " gets default 3 armies." << std::endl;
        }
        else {
            int armiesToGive = numberTerritoriesByPlayer / 3;
            player->armyPool += armiesToGive;
            std::cout << player->getName() << " gets default " << armiesToGive << " armies." << std::endl;
        }
        for(Continent *continent : this->map->listOfContinents) {
            if (continent->isOwnedByPlayer(player)) {           //if player owns all territories of continent
                player->armyPool += continent->getArmyValue();
                std::cout << player->getName() << " gets additional " << continent->getArmyValue() << " armies as continent bonus for owning the entirety of " << continent->getContName() << std::endl;
            }
        }
        std::cout << player->getName() << " can deploy a total of " << player->armyPool << " troops." << std::endl << std::endl;
    }
    transition(new Command(GameEngine::GameCommand::issue_order)); // change state to issue order
}

/**
 * For each player, issue order. Call to issueOrder()
 */
void GameEngine::issueOrdersPhase()
{
    std::cout << "*Issue Orders Phase*" << std::endl << std::endl;
    for (Player* player : this->players) {
        std::cout << player->getName() << "'s Turn!" << std::endl << std::endl;
        player->issueOrder(deck,map,players);
    }
    transition(new Command(GameEngine::GameCommand::end_issue_order)); // change state to end issue order
}

/**
 * Executes the order. Removes order from orderlist
 */
void GameEngine::executeOrdersPhase()
{
    std::cout << "*Execution Phase*" << std::endl << std::endl;
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
}

/**
 * Executes the order. Removes order from orderlist
 */
void GameEngine::setupTournamentGame()
{
    if (mapCounter < this->listOfMapFileNames.size()){
        // Load map
        auto params = std::vector<std::string>();
        params.push_back(this->listOfMapFileNames.at(mapCounter));
        this->transition(new Command(GameCommand::load_map, params));

        // Validate map
        this->transition(new Command(GameCommand::validate_map));

        // Add players
        int counter = 1;
        for (PlayerStrategy::StrategyType strategyType: *this->listOfPlayerStrategies){
            params = std::vector<std::string>();
            params.push_back("Computer" + std::to_string(counter++));
            params.push_back(PlayerStrategy::strategyTypeMapping.at(strategyType));
            this->transition(new Command(GameCommand::add_player,params));
        }

        // Start game
        this->transition(new Command(GameCommand::game_start));
    } else {
        std::cout << "Tournament done";
        logTournamentResults();
        notify(this);
        exit(0);
    }
}

void GameEngine::validateTournamentParameters(Command* command)
{
    // Get and validate List of Maps
    boost::split(listOfMapFileNames, command->getParams()[0], boost::is_any_of(","));
    if (listOfMapFileNames.empty())
        throw std::runtime_error("No maps provided");
    if (listOfMapFileNames.size() > 5)
        throw std::runtime_error("Cannot have more than 5 maps");

    // Get and validate List of Player Strategies
    std::vector<std::string> listOfPlayerStrategyNames;
    this->listOfPlayerStrategies = new std::vector<PlayerStrategy::StrategyType>();
    boost::split(listOfPlayerStrategyNames, command->getParams()[1], boost::is_any_of(","));
    if (listOfPlayerStrategyNames.empty())
        throw std::runtime_error("No player strategies provided");
    if (listOfPlayerStrategyNames.size() < 2 or listOfPlayerStrategyNames.size() > 4)
        throw std::runtime_error("Must have between 2 and 4 players");
    for (const std::string& strategy: listOfPlayerStrategyNames){
        bool isValidStrategy = false;
        for (auto& it: PlayerStrategy::strategyTypeMapping){
            if (it.second == strategy) {
                isValidStrategy = true;
                listOfPlayerStrategies->push_back(it.first);
                break;
            }
        }
        if (!isValidStrategy)
            throw std::runtime_error(strategy + " is an invalid Player Strategy");
    }

    // Get and validate number of games
    try {
        this->numberOfGames = std::stoi(command->getParams()[2]);
        if (this->numberOfGames < 0 or this->numberOfGames > 5)
            throw std::runtime_error("Number of games must be between 1 and 5");
    } catch (std::invalid_argument&){
        throw std::runtime_error(command->getParams()[2] + " is an invalid argument provided");
    }

    // Get and validate number of turns
    try {
        this->maxNumberOfTurns = std::stoi(command->getParams()[3]);
        if (this->maxNumberOfTurns < 10 or this->maxNumberOfTurns > 50)
            throw std::runtime_error("Number of turns per game must be between 10 and 50");
    } catch (std::invalid_argument&){
        throw std::runtime_error(command->getParams()[3] + " is an invalid argument provided");
    }

    // Validate each map
    for (const std::string& mapFileName: listOfMapFileNames){
        Map* tempMap = new Map(mapFileName);
        auto mapLoader = MapLoader(mapFileName);
        mapLoader.readMap(tempMap);
        if (!tempMap->validate())
            throw std::runtime_error(mapFileName + " is an invalid map");

        // Setup map results
        this->tournamentResults.insert(std::pair<std::string, std::vector<std::string>>(mapFileName, std::vector<std::string>()));
    }
}

/**
 * Main Game Loop containing 3 phases: Reinforcement Phase, Issue Orders Phase, and execute Orders Phase
 * Loop continues until one of the players owns all territories in map. If player does
 * not control at least one territory, player is removed from game
 *
 */
void GameEngine::mainGameLoop(CommandProcessor* commandProcessor)
{
    while (*this->current_state != GameState::end) {
        if (numberOfGames != -1 && gameCounter > numberOfGames) {
            mapCounter++; // move to next map
            gameCounter = 1; // reset game counter
        }

        if (tournamentMode)
            setupTournamentGame();
        else
            startupPhase(commandProcessor);

        bool playing = true;
        while(playing){
            if (maxNumberOfTurns != -1 && turnCounter++ >= maxNumberOfTurns) {
                // end game, draw
                std::cout << std::endl << "\x1B[32m" << "Game Over! It was a draw" << "\033[0m" << std::endl << std::endl;
                *this->current_state = GameState::start;
                playing = false;
                addWinnerToResults("draw");
                resetGame();
            } else {
                bool allContinents;
                for(Player* player: this->players) {
                    allContinents = true;
                    for(Continent* continent: map->listOfContinents){
                        if(!continent->isOwnedByPlayer(player)){
                            allContinents = false;
                        }
                    }
                    if(map->getTerritoriesByPlayer(player).empty()){
                        removePlayer(player->getName());
                    }
                }
                if(allContinents){
                    playing = false;
                    addWinnerToResults(PlayerStrategy::strategyTypeMapping.at(map->listOfTerritories.at(0)->getOwner()->getStrategyType()));
                    std::cout << std::endl << "\x1B[32m" << "Game over! Player (" << map->listOfTerritories.at(0)->getOwner()->getName() << ") Won!" << "\033[0m" << std::endl << std::endl;
                    if (tournamentMode) {
                        this->transition(new Command(GameCommand::win_game));
                        this->transition(new Command(GameCommand::replay));
                    }
                    else
                        while (*this->current_state != GameState::start and *this->current_state != GameState::end)
                            this->transition(commandProcessor->getCommand());
                    resetGame();
                }
                else {
                    if (*this->current_state == GameState::execute_orders)
                        transition(new Command(GameEngine::GameCommand::end_execute_order)); // change state to end execute order
                    reinforcementPhase();
                    issueOrdersPhase();
                    executeOrdersPhase();
                }
            }
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
        std::cout << std::endl << "Total Number of Continents: " << map->listOfContinents.size() << std::endl;
        std::cout << "Total Number of Territories: " << map->listOfTerritories.size() << std::endl;
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
            if (player->getName() == command->getParams()[0]) {
                effect = "Player (name: " + command->getParams()[0] + ", strategy: " + command->getParams()[1] + ") already exist";
                std::cout << std::endl << "\x1B[31m" << effect << "\033[0m" << std::endl << std::endl;
                found = true;
            }
        }
        if (!found) {
            effect = "Player (name: " + command->getParams()[0] + ", strategy: " + command->getParams()[1] + ") added";
            std::cout << std::endl << "\x1B[32m" << effect << "\033[0m" << std::endl << std::endl;
            try {
                PlayerStrategy::StrategyType strategyType = getStrategyType(command->getParams()[1]);
                auto* player = new Player(command->getParams()[0], strategyType);
                attachExistingObservers(player->orderList);
                this->players.push_back(player);
            } catch (std::runtime_error&){
                std::cout << std::endl << "\x1B[31m" << "Invalid strategy type" << "\033[0m" << std::endl << std::endl;
            }
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
    std::cout << std::endl << "The order of play will be: " << std::endl;

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
        std::cout << *player << std::endl;
    }
}
/**
 * Prints available commands
 */
void GameEngine::printAvailableCommands(){
    std::cout << "Available commands:" << std::endl;
    std::vector<GameEngine::GameCommand> commands;
    getAvailableCommands(commands);
    int counter = 1;
    for (GameEngine::GameCommand command: commands){
        std::cout << counter++ << ". " << command << std::endl;
    }
}

/**
 * Game state to string
 * @return currentState of game
 */
std::string GameEngine::stringToLog() {
    if (toPrint.empty()){
        std::string strGameState;
        for (auto& it: GameEngine::gameStateMapping){
            if (it.second == *this->current_state)
                strGameState = it.first;
        }
        return "Game Engine new state: " + strGameState;
    } else
        return toPrint;
}

void GameEngine::attachExistingObservers(Subject *subject) {
    for (Observer* observer: this->getObservers())
        subject->attach(observer);
}

void GameEngine::resetGame()
{
    delete this->deck;
    this->deck = new Deck();
    delete this->map;
    this->map = new Map();
    for (Player* player: this->players)
        delete player;
    this->players = std::vector<Player*>();
    this->turnCounter = 0;
}

void GameEngine::logTournamentResults()
{
    // Get table
    this->toPrint = "\n============================\n";
    this->toPrint += "Tournament Mode: \nM: ";
    int counter = 1;
    for (const std::string& mapFileName: this->listOfMapFileNames){
        if (counter++ == this->listOfMapFileNames.size())
            this->toPrint += mapFileName + "\n";
        else
            this->toPrint += mapFileName + ",";
    }
    this->toPrint += "P: ";
    counter = 1;
    for (const PlayerStrategy::StrategyType strategyType: *this->listOfPlayerStrategies){
        if (counter++ == this->listOfPlayerStrategies->size())
            this->toPrint += PlayerStrategy::strategyTypeMapping.at(strategyType) + "\n";
        else
            this->toPrint += PlayerStrategy::strategyTypeMapping.at(strategyType) + ",";
    }
    this->toPrint += "G: " + std::to_string(numberOfGames) + "\n";
    this->toPrint += "D: " + std::to_string(maxNumberOfTurns) + "\n\n";
    this->toPrint += "Results: \n";
    for (const auto& pair: this->tournamentResults) {
        this->toPrint += "Map (" + pair.first + "): ";
        counter = 0;
        for (const auto& winner: pair.second){
            if (++counter == pair.second.size())
                this->toPrint += "Game (" + std::to_string(counter) + "): " + winner + " \n";
            else
                this->toPrint += "Game (" + std::to_string(counter) + "): " + winner + " | ";
        }
    }
    this->toPrint += "============================\n";
}

void GameEngine::addWinnerToResults(const std::string& winner)
{
    this->tournamentResults.at(this->map->getMapName()).push_back(winner);
    gameCounter++;
}
