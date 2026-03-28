cmake_minimum_required(VERSION 4.0)
project(P2_Group_33)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(P2_Group_33
        include/AStar.h
        include/DataLoader.h
        include/Dijkstra.h
        include/Graph.h
        include/Menu.h
        src/AStar.cpp
        src/DataLoader.cpp
        src/Dijkstra.cpp
        src/Graph.cpp
        src/main.cpp
        src/Menu.cpp
        src/Dijkstra.cpp)
