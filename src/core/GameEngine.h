#pragma once

#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
#include <map>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "LoggingObserver.h"

class CommandProcessor;

class GameEngine : public Subject{
public:
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
    GameEngine();
    // Copy constructor
    GameEngine(const GameEngine&);
    // Assignment operator
    GameEngine& operator= (const GameEngine&);
    // Stream output operator
    friend std::ostream& operator<< (std::ostream&, const GameEngine&);
    friend std::ostream& operator<< (std::ostream&, const GameCommand&);
    bool operator== (const GameEngine&) const;
    GameState& getGameState();
    vector<Player *> &getPlayers();
    Map& getMap();
    Deck& getDeck();
    void getAvailableCommands(std::vector<GameCommand>&);
    void transition(GameCommand&, const std::string& param);
    void startupPhase(CommandProcessor*);
    void mainGameLoop();
    std::string stringToLog();

    static const boost::unordered_map<std::string, GameState> gameStateMapping;
    static const boost::unordered_map<std::string, GameCommand> gameCommandMapping;

private:
    GameState *current_state;
    std::vector<Player*>* players;
    Map* map;
    Deck* deck;
    void printAvailableCommands();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();
    bool containsOrders(std::map<Player*, bool>);
    void loadMap(const std::string& mapName);
    void validateMap();
    void addPlayer(const std::string& playerName);
    void removePlayer(const std::string& playerName);
    void gameStart();
};