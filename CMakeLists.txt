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

aux_source_directory(src/core CORE)

aux_source_directory(tests TESTS)

add_executable(tests ${CMAKE_SOURCE_DIR}/${TESTS} ${CMAKE_SOURCE_DIR}/${CORE})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_executable(main ${CMAKE_SOURCE_DIR}/src/driver/MainDriver.cpp ${CMAKE_SOURCE_DIR}/${CORE})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)