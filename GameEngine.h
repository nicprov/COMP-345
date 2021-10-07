#ifndef COMP354_GAMEENGINE_H
#define COMP354_GAMEENGINE_H
#include <vector>
class GameEngine{
public:
    enum Game_State{
        start=1,
        map_loaded=2,
        map_validated=3,
        players_added=4,
        assign_reinforcement=5,
        issue_orders=6,
        execute_orders=7,
        win=8
    };
    enum Game_Command{
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
    Game_State& getGameState();
    std::vector<Game_Command>& getAvailableCommands();
    bool transition(Game_Command&);
private:
    Game_State current_state;
};
#endif //COMP354_GAMEENGINE_H
