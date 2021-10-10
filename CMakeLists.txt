cmake_minimum_required(VERSION 3.5)
project(comp354)

find_package(Catch2 3 REQUIRED)
add_executable(tests ${CMAKE_SOURCE_DIR}/src/Cards.cpp ${CMAKE_SOURCE_DIR}/src/GameEngine.cpp ${CMAKE_SOURCE_DIR}/tests/Test_Cards.cpp ${CMAKE_SOURCE_DIR}/tests/Test_GameEngine.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_executable(main ${CMAKE_SOURCE_DIR}/src/MainDriver.cpp ${CMAKE_SOURCE_DIR}/src/Cards.cpp ${CMAKE_SOURCE_DIR}/src/GameEngine.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)