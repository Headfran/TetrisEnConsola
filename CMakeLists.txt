cmake_minimum_required(VERSION 3.17)

project(TetrisCmd)

set(CMAKE_CXX_STANDARD 17)

set(GAME_PATH "${CMAKE_CURRENT_LIST_DIR}/Classes")

add_executable(TetrisCMD main.cpp
    ${GAME_PATH}/Game.h ${GAME_PATH}/Game.cpp
    ${GAME_PATH}/Bloque.h ${GAME_PATH}/Bloque.cpp
    ${GAME_PATH}/Vector2.h ${GAME_PATH}/Vector2.cpp
    ${GAME_PATH}/Timer.h ${GAME_PATH}/Timer.cpp)
