cmake_minimum_required(VERSION 3.10)
project(minesweeper LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(minesweeper
    main.cpp
    Board.cpp
    Game.cpp
)