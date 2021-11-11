#ifndef COMP354_GAMEENGINE_H
#define COMP354_GAMEENGINE_H
#include <vector>
#include <map>
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
#include "Player.h"
#include "Map.h"

class GameEngine{
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
    void getAvailableCommands(std::vector<GameCommand>&);
    void transition(GameCommand&);
    static const boost::unordered_map<std::string, GameCommand> gameCommandMapping;

    void addPlayer(Player*);

    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

private:
    GameState *current_state;
    std::vector<Player*>* players;
    bool containsOrders(std::map<Player*, bool>);
    Map* currentMap;
};
#endif //COMP354_GAMEENGINE_H
