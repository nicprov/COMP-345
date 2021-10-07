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

void GameEngine::operator=(const GameEngine &gameEngine)
{
    current_state = gameEngine.current_state;
}

GameEngine::Game_State& GameEngine::getGameState()
{
    return current_state;
}

vector<GameEngine::Game_Command> GameEngine::getAvailableCommands()
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

void GameEngine::transition(Game_Command &gameCommand)
{
    bool foundCommand = false;
    for (Game_Command gameCommand_: getAvailableCommands()){
        if (gameCommand_ == gameCommand) {
            foundCommand = true;
            // Perform move
            switch (gameCommand){
                case load_map:
                    cout << endl << "\x1B[32m" << "Map loaded" << "\033[0m" << endl << endl;
                    current_state = map_loaded;
                    break;
                case validate_map:
                    cout << endl << "\x1B[32m" << "Map validated" << "\033[0m" << endl << endl;
                    current_state = map_validated;
                    break;
                case add_player:
                    cout << endl << "\x1B[32m" << "Players added" << "\033[0m" << endl << endl;
                    current_state = players_added;
                    break;
                case assign_countries:
                    cout << endl << "\x1B[32m" << "Assign reinforcement" << "\033[0m" << endl << endl;
                    current_state = assign_reinforcement;
                    break;
                case issue_order:
                    cout << endl << "\x1B[32m" << "Issue orders" << "\033[0m" << endl << endl;
                    current_state = issue_orders;
                    break;
                case end_issue_orders:
                    cout << endl << "\x1B[32m" << "End issue orders" << "\033[0m" << endl << endl;
                    current_state = execute_orders;
                    break;
                case execute_order:
                    cout << endl << "\x1B[32m" << "Execute orders" << "\033[0m" << endl << endl;
                    current_state = execute_orders;
                    break;
                case end_execute_order:
                    cout << endl << "\x1B[32m" << "End execute orders" << "\033[0m" << endl << endl;
                    current_state = assign_reinforcement;
                    break;
                case win_game:
                    cout << endl << "\x1B[32m" << "Win game" << "\033[0m" << endl << endl;
                    current_state = win;
                    break;
                case play:
                    cout << endl << "\x1B[32m" << "Play game" << "\033[0m" << endl << endl;
                    current_state = start;
                    break;
                case end:
                    cout << endl << "\x1B[32m" << "Exiting game" << "\033[0m" << endl << endl;
                    exit(0);
            }
        }
    }
    if (!foundCommand)
        cout << endl << "\x1B[31m" << "Invalid input" << "\033[0m" << endl << endl;
}

ostream& operator<< (ostream &stream, const GameEngine &gameEngine)
{
    return stream << "Current state (" << gameEngine.current_state << ")";
}

ostream &operator<<(ostream &stream, const GameEngine::Game_Command &gameCommand) {
    switch (gameCommand) {
        case GameEngine::Game_Command::load_map:
            stream << "Load Map";
            break;
        case GameEngine::Game_Command::validate_map:
            stream << "Validate Map";
            break;
        case GameEngine::Game_Command::add_player:
            stream << "Add player";
            break;
        case GameEngine::Game_Command::assign_countries:
            stream << "Assign countries";
            break;
        case GameEngine::Game_Command::issue_order:
            stream << "Issue order";
            break;
        case GameEngine::Game_Command::end_issue_orders:
            stream << "End issue order";
            break;
        case GameEngine::Game_Command::execute_order:
            stream << "Execute order";
            break;
        case GameEngine::Game_Command::end_execute_order:
            stream << "End execute order";
            break;
        case GameEngine::Game_Command::win_game:
            stream << "Win game";
            break;
        case GameEngine::Game_Command::play:
            stream << "Play game";
            break;
        case GameEngine::Game_Command::end:
            stream << "End";
            break;
    }
    return stream;
}
