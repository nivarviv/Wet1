cmake_minimum_required(VERSION 3.20)
project(Wet1)

set(CMAKE_CXX_STANDARD 11)

#include_directories(.)

add_executable(
        Wet1
        main23a1.cpp
        wet1util.h
        worldcup23a1.cpp
        worldcup23a1.h
        team.cpp
        team.h
        player.cpp
        player.h
        AvlTree.h
        playerStats.cpp
        playerStats.h
        node.h)
