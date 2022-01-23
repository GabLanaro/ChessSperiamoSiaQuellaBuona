cmake_minimum_required(VERSION 2.8)

project(scacchiera)
project(replay)

include_directories(include)

add_library(board
   include/board.h
   src/board.cpp 
)

add_library(game
    include/game.h
    src/game.cpp
)

add_library(pezzo
    include/pezzo.h
    src/pezzo.cpp
)

add_library(player 
    include/player.h
    src/player.cpp
)

add_executable(scacchiera
    src/scacchiera.cpp
)

add_executable(replay   
    src/replay.cpp
)

target_link_libraries(scacchiera
    game
    board
    player
    pezzo 
)