#include <iostream>
#include "GameEngine.h"

GameEngine::GameEngine()
{
    this->current_state = new GameState(GameState::start);
}

GameEngine::GameEngine(const GameEngine *gameEngine)
{
    this->current_state = new GameState(*gameEngine->current_state);
}

GameEngine& GameEngine::operator=(const GameEngine &gameEngine)
{
    this->current_state = new GameState(*gameEngine.current_state);
    return *this;
}

GameEngine::GameState& GameEngine::getGameState()
{
    return *current_state;
}

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
            availableCommands.push_back(GameCommand::assign_countries);
            break;
        case assign_reinforcement:
            availableCommands.push_back(GameCommand::issue_order);
            break;
        case issue_orders:
            availableCommands.push_back(GameCommand::issue_order);
            availableCommands.push_back(GameCommand::end_issue_orders);
            break;
        case execute_orders:
            availableCommands.push_back(GameCommand::execute_order);
            availableCommands.push_back(GameCommand::end_execute_order);
            availableCommands.push_back(GameCommand::win_game);
            break;
        case win:
            availableCommands.push_back(GameCommand::play);
            availableCommands.push_back(GameCommand::end);
            break;
    }
}

void GameEngine::transition(GameCommand &gameCommand)
{
    bool foundCommand = false;
    std::vector<GameCommand> commands;
    getAvailableCommands(commands);
    for (GameCommand gameCommand_: commands){
        if (gameCommand_ == gameCommand) {
            foundCommand = true;
            // Perform move
            switch (gameCommand){
                case load_map:
                    std::cout << std::endl << "\x1B[32m" << "Map loaded" << "\033[0m" << std::endl << std::endl;
                    *current_state = map_loaded;
                    break;
                case validate_map:
                    std::cout << std::endl << "\x1B[32m" << "Map validated" << "\033[0m" << std::endl << std::endl;
                    *current_state = map_validated;
                    break;
                case add_player:
                    std::cout << std::endl << "\x1B[32m" << "Players added" << "\033[0m" << std::endl << std::endl;
                    *current_state = players_added;
                    break;
                case assign_countries:
                    std::cout << std::endl << "\x1B[32m" << "Assign reinforcement" << "\033[0m" << std::endl << std::endl;
                    *current_state = assign_reinforcement;
                    break;
                case issue_order:
                    std::cout << std::endl << "\x1B[32m" << "Issue orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = issue_orders;
                    break;
                case end_issue_orders:
                    std::cout << std::endl << "\x1B[32m" << "End issue orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = execute_orders;
                    break;
                case execute_order:
                    std::cout << std::endl << "\x1B[32m" << "Execute orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = execute_orders;
                    break;
                case end_execute_order:
                    std::cout << std::endl << "\x1B[32m" << "End execute orders" << "\033[0m" << std::endl << std::endl;
                    *current_state = assign_reinforcement;
                    break;
                case win_game:
                    std::cout << std::endl << "\x1B[32m" << "Win game" << "\033[0m" << std::endl << std::endl;
                    *current_state = win;
                    break;
                case play:
                    std::cout << std::endl << "\x1B[32m" << "Play game" << "\033[0m" << std::endl << std::endl;
                    *current_state = start;
                    break;
                case end:
                    std::cout << std::endl << "\x1B[32m" << "Exiting game" << "\033[0m" << std::endl << std::endl;
                    exit(0);
            }
        }
    }
    if (!foundCommand)
        std::cout << std::endl << "\x1B[31m" << "Invalid input" << "\033[0m" << std::endl << std::endl;
}

std::ostream& operator<< (std::ostream &stream, const GameEngine &gameEngine)
{
    return stream << "Current state (" << gameEngine.current_state << ")";
}

std::ostream &operator<< (std::ostream &stream, const GameEngine::GameCommand &gameCommand)
{
    switch (gameCommand) {
        case GameEngine::GameCommand::load_map:
            stream << "Load Map";
            break;
        case GameEngine::GameCommand::validate_map:
            stream << "Validate Map";
            break;
        case GameEngine::GameCommand::add_player:
            stream << "Add player";
            break;
        case GameEngine::GameCommand::assign_countries:
            stream << "Assign countries";
            break;
        case GameEngine::GameCommand::issue_order:
            stream << "Issue order";
            break;
        case GameEngine::GameCommand::end_issue_orders:
            stream << "End issue order";
            break;
        case GameEngine::GameCommand::execute_order:
            stream << "Execute order";
            break;
        case GameEngine::GameCommand::end_execute_order:
            stream << "End execute order";
            break;
        case GameEngine::GameCommand::win_game:
            stream << "Win game";
            break;
        case GameEngine::GameCommand::play:
            stream << "Play game";
            break;
        case GameEngine::GameCommand::end:
            stream << "End";
            break;
    }
    return stream;
}

bool GameEngine::operator==(const GameEngine &gameEngine) const
{
    return this->current_state == gameEngine.current_state;
}
