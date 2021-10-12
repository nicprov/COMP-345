cmake_minimum_required(VERSION 3.11)
project(comp354)
set(CMAKE_CXX_STANDARD 20)

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests ${CMAKE_SOURCE_DIR}/src/Map.cpp ${CMAKE_SOURCE_DIR}/src/Player.cpp ${CMAKE_SOURCE_DIR}/src/Orders.cpp ${CMAKE_SOURCE_DIR}/src/Cards.cpp ${CMAKE_SOURCE_DIR}/src/GameEngine.cpp ${CMAKE_SOURCE_DIR}/tests/Test_Cards.cpp ${CMAKE_SOURCE_DIR}/tests/Test_GameEngine.cpp ${CMAKE_SOURCE_DIR}/tests/Test_Orders.cpp ${CMAKE_SOURCE_DIR}/tests/Test_Map.cpp ${CMAKE_SOURCE_DIR}/tests/Test_Player.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_executable(main ${CMAKE_SOURCE_DIR}/src/MainDriver.cpp ${CMAKE_SOURCE_DIR}/src/Cards.cpp ${CMAKE_SOURCE_DIR}/src/GameEngine.cpp ${CMAKE_SOURCE_DIR}/src/Orders.cpp ${CMAKE_SOURCE_DIR}/src/Map.cpp ${CMAKE_SOURCE_DIR}/src/Player.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
