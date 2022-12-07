# cmake_minimum_required(VERSION <specify CMake version here>)
project(wet1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(wet1
        main23a1.cpp
        wet1util.h
        worldcup23a1.cpp
        worldcup23a1.h team.cpp team.h player.cpp player.h AvlTree.h playerStats.cpp playerStats.h)
