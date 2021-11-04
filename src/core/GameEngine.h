#ifndef COMP354_GAMEENGINE_H
#define COMP354_GAMEENGINE_H
#include <vector>

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
        replay=10,
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
    void transition(GameCommand&);
private:
    GameState *current_state;
};
#endif //COMP354_GAMEENGINE_H
