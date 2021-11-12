cmake_minimum_required(VERSION 3.11)

project(comp354)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

fetchContent_declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
)

fetchContent_declare(
        boostorg
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG        master
)

fetchContent_makeAvailable(Catch2)

fetchContent_makeAvailable(boostorg)

aux_source_directory(src/core CORE)

aux_source_directory(tests TESTS)

add_executable(tests ${CMAKE_SOURCE_DIR}/${TESTS} ${CMAKE_SOURCE_DIR}/${CORE})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain Boost::algorithm Boost::assign)

add_executable(main ${CMAKE_SOURCE_DIR}/src/driver/MainDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

add_executable(cards ${CMAKE_SOURCE_DIR}/src/driver/CardsDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

add_executable(commandProcessing ${CMAKE_SOURCE_DIR}/src/driver/CommandProcessingDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

add_executable(gameEngine ${CMAKE_SOURCE_DIR}/src/driver/GameEngineDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

add_executable(map ${CMAKE_SOURCE_DIR}/src/driver/MapDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

add_executable(logObserver ${CMAKE_SOURCE_DIR}/src/driver/LogObserverDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

add_executable(orders ${CMAKE_SOURCE_DIR}/src/driver/OrdersDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

add_executable(player ${CMAKE_SOURCE_DIR}/src/driver/PlayerDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

target_link_libraries(main Boost::algorithm Boost::assign)

target_link_libraries(cards Boost::algorithm Boost::assign)

target_link_libraries(commandProcessing Boost::algorithm Boost::assign)

target_link_libraries(gameEngine Boost::algorithm Boost::assign)

target_link_libraries(logObserver Boost::algorithm Boost::assign)

target_link_libraries(map Boost::algorithm Boost::assign)

target_link_libraries(orders Boost::algorithm Boost::assign)

target_link_libraries(player Boost::algorithm Boost::assign)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)