#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "../src/GameEngine.h"

/**
 * GameEngine Test cases
 */
TEST_CASE("Game engine constructor initializes")
{
    GameEngine gameEngine = GameEngine();
    REQUIRE(gameEngine.getGameState() == GameEngine::GameState::start);
}

TEST_CASE("Game engine copy constructor initializes")
{
    GameEngine gameEngine;
    GameEngine::GameCommand command = GameEngine::GameCommand::load_map;
    gameEngine.transition(command);
    GameEngine gameEngine2 = GameEngine(gameEngine);
    REQUIRE(gameEngine == gameEngine2);
}

TEST_CASE("Game engine assignment operator initializes")
{
    GameEngine gameEngine;
    GameEngine::GameCommand command = GameEngine::GameCommand::load_map;
    gameEngine.transition(command);
    GameEngine gameEngine2 = gameEngine;
    REQUIRE(gameEngine == gameEngine2);
}

TEST_CASE("Game engine get game state")
{
    GameEngine gameEngine;
    REQUIRE(gameEngine.getGameState() == GameEngine::GameState::start);
}

TEST_CASE("Game engine get available commands")
{
    GameEngine gameEngine;
    std::vector<GameEngine::GameCommand> commands;
    gameEngine.getAvailableCommands(commands);
    REQUIRE(commands.size() == 1);
    REQUIRE(std::find(commands.begin(), commands.end(), GameEngine::GameCommand::load_map) != commands.end());
}

TEST_CASE("Game engine transition")
{
    GameEngine gameEngine;
    GameEngine::GameCommand command = GameEngine::GameCommand::load_map;
    gameEngine.transition(command);
    REQUIRE(gameEngine.getGameState() == GameEngine::GameState::map_loaded);
}

