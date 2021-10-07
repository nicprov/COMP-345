#include <iostream>
#include "GameEngine.h"
using namespace std;

GameEngine::GameEngine()
{
    current_state = Game_State::start;
}

GameEngine::GameEngine(const GameEngine &gameEngine)
{
    current_state = gameEngine.current_state;
}

GameEngine& GameEngine::operator=(const GameEngine &gameEngine)
{
    current_state = gameEngine.current_state;
}

GameEngine::Game_State& GameEngine::getGameState()
{
    return current_state;
}

vector<GameEngine::Game_Command>& GameEngine::getAvailableCommands()
{
    vector<GameEngine::Game_Command> availableCommands;
    switch (current_state) {
        case start:
            availableCommands.push_back(Game_Command::load_map);
            break;
        case map_loaded:
            availableCommands.push_back(Game_Command::load_map);
            availableCommands.push_back(Game_Command::validate_map);
            break;
        case map_validated:
            availableCommands.push_back(Game_Command::add_player);
            break;
        case players_added:
            availableCommands.push_back(Game_Command::add_player);
            availableCommands.push_back(Game_Command::assign_countries);
            break;
        case assign_reinforcement:
            availableCommands.push_back(Game_Command::issue_order);
            break;
        case issue_orders:
            availableCommands.push_back(Game_Command::issue_order);
            availableCommands.push_back(Game_Command::end_issue_orders);
            break;
        case execute_orders:
            availableCommands.push_back(Game_Command::execute_order);
            availableCommands.push_back(Game_Command::end_issue_orders);
            availableCommands.push_back(Game_Command::win_game);
            break;
        case win:
            availableCommands.push_back(Game_Command::play);
            availableCommands.push_back(Game_Command::end);
            break;
    }
    return availableCommands;
}

bool GameEngine::transition(Game_Command &gameCommand)
{
    for (Game_Command gameCommand_: getAvailableCommands()){
        if (gameCommand_ == gameCommand) {
            // Perform move
            switch (gameCommand){
                case load_map:
                    cout << "Map loaded";
                    current_state = map_loaded;
                    break;
                case validate_map:
                    cout << "Map validated";
                    current_state = map_validated;
                    break;
                case add_player:
                    cout << "Players added";
                    current_state = players_added;
                    break;
                case assign_countries:
                    cout << "Assign reinforcement";
                    current_state = assign_reinforcement;
                    break;
                case issue_order:
                    cout << "Issue orders";
                    current_state = issue_orders;
                    break;
                case end_issue_orders:
                    cout << "End issue orders";
                    current_state = execute_orders;
                    break;
                case execute_order:
                    cout << "Execute orders";
                    current_state = execute_orders;
                    break;
                case end_execute_order:
                    cout << "End execute orders";
                    current_state = assign_reinforcement;
                    break;
                case win_game:
                    cout << "Win game";
                    current_state = win;
                    break;
                case play:
                    cout << "Play game";
                    current_state = start;
                    break;
                case end:
                    exit(0);
            }
            return true;
        }
    }
    return false;
}

std::ostream& operator<< (std::ostream &stream, const GameEngine &gameEngine)
{
    return stream << "Current state (" << gameEngine.current_state << ")";
}