cmake_minimum_required(VERSION 3.10)

# set the project name
project(Scacchiera)

# add the executable
add_executable(Scacchiera scacchiera.cpp board.cpp game.cpp pezzo.cpp player.cpp)