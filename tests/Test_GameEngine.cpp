#include <catch2/catch_test_macros.hpp>
#include "../src/core/GameEngine.h"

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
    auto* gameEngine = new GameEngine();
    auto* gameEngine2 = new GameEngine(*gameEngine);
    REQUIRE(*gameEngine == *gameEngine2);
}

TEST_CASE("Game engine assignment operator initializes")
{
    auto* gameEngine = new GameEngine();
    auto* gameEngine2 = new GameEngine(*gameEngine);
    REQUIRE(*gameEngine == *gameEngine2);
}

TEST_CASE("Game engine get game state")
{
    auto* gameEngine = new GameEngine();
    REQUIRE(gameEngine->getGameState() == GameEngine::GameState::start);
}

TEST_CASE("Game engine get available commands")
{
    auto* gameEngine = new GameEngine();
    std::vector<GameEngine::GameCommand> commands;
    gameEngine->getAvailableCommands(commands);
    REQUIRE(commands.size() == 2);
    REQUIRE(std::find(commands.begin(), commands.end(), GameEngine::GameCommand::load_map) != commands.end());
}

