cmake_minimum_required(VERSION 3.20)
project(comp354)

set(CMAKE_CXX_STANDARD 23)

add_executable(main Cards.h Cards.cpp CardsDriver.cpp GameEngine.h GameEngine.cpp GameEngineDriver.cpp)