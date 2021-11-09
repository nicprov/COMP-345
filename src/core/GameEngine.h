#ifndef COMP354_GAMEENGINE_H
#define COMP354_GAMEENGINE_H
#include <vector>
<<<<<<< Updated upstream
=======
#include <map>
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
#include "Player.h"
//#include "CommandProcessing.h"
#include "Map.h"
#include "Cards.h"
>>>>>>> Stashed changes

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
        assign_countries=4,
        issue_order=5,
        end_issue_orders=6,
        execute_order=7,
        end_execute_order=8,
        win_game=9,
        play=10,
        end=11
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
    void loadMap();
    void validateMap();
    void addPlayers();
    void gameStart();
    void transition(GameCommand&);
<<<<<<< Updated upstream
private:
    GameState *current_state;
=======
    static const boost::unordered_map<std::string, GameCommand> gameCommandMapping;

    void registerPlayer(Player*);

    void startupPhase(GameEngine& gameEngine);
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

private:
    GameState *current_state;
    std::vector<Player*>* players;
    Map* map;
    Deck* deck;
    bool containsOrders(std::map<Player*, bool>);
>>>>>>> Stashed changes
};

void listAvailableCommands(GameEngine& gameEngine);
#endif COMP354_GAMEENGINE_H
