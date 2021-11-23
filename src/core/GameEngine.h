#pragma once //include guards

#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
#include <map>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "LoggingObserver.h"

//class forward reference
class CommandProcessor;
class Command;

class GameEngine : public Subject{
public:
    //list of Game states
    enum GameState{
        start=1,
        map_loaded=2,
        map_validated=3,
        players_added=4,
        assign_reinforcement=5,
        issue_orders=6,
        execute_orders=7,
        win=8
    };
    //list of game commands
    enum GameCommand{
        load_map=1,
        validate_map=2,
        add_player=3,
        game_start=4,
        issue_order=5,
        end_issue_order=6,
        execute_order=7,
        end_execute_order=8,
        win_game=9,
        replay=10,
        quit=11
    };
    GameEngine();   //Game Engine Constructor
    GameEngine(const GameEngine&); // Copy constructor
    GameEngine& operator= (const GameEngine&); // Assignment operator
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const GameEngine&);
    friend std::ostream& operator<< (std::ostream&, const GameCommand&);
    bool operator== (const GameEngine&) const; //comparison of player
    GameState& getGameState();   //getter for current game state
    std::vector<Player *> &getPlayers(); //getter of players in a vector pointer
    Map& getMap();  //getter for map
    Deck& getDeck(); // getter for deck
    void getAvailableCommands(std::vector<GameCommand>&);   //get Available Commands
    void transition(Command*);    // transition game state based on command
    void mainGameLoop(CommandProcessor*);    //main game loop: includes call to reinforcement phase, issue order phase, and execute orders phase
    std::string stringToLog();  //current game state to string

    static const boost::unordered_map<std::string, GameState> gameStateMapping;
    static const boost::unordered_map<std::string, GameCommand> gameCommandMapping;
private:
    GameState* current_state;
    std::vector<Player*> players;
    Map* map;
    Deck* deck;
    void attachExistingObservers(Subject*); // Attach all current observers to the passed subject
    void printAvailableCommands();  //prints available commands
    void startupPhase(CommandProcessor*);   //Startup phase of the game
    void reinforcementPhase();      //assign armies to reinforcement pool
    void issueOrdersPhase();        // call to issue order
    void executeOrdersPhase();      //executes order
    bool containsOrders(const std::map<Player*, bool>&);   //check if player contains orders
    void loadMap(const std::string& mapName);       //load map
    void validateMap(); // validate map based on conditions
    void addPlayer(Command*);  //enter players in game
    void removePlayer(const std::string& playerName);   //remove player
    void gameStart();   // set-up for start of game
};