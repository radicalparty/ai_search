cmake_minimum_required(VERSION 3.30)
project(ai_search)

set(CMAKE_CXX_STANDARD 20)

add_executable(ai_search main.cpp
        5/Maze/AlterMazeState.cpp
        5/Maze/AlterMazeState.h
        5/Maze/Character.cpp
        5/Maze/Character.h
        5/playGame/play.cpp
        5/playGame/play.h
        5/playGame/minimax.cpp
        5/playGame/minimax.h
        5/playGame/montecarlo.cpp
        5/playGame/montecarlo.h
        5/playGame/thunder.cpp
        5/playGame/thunder.h
)
