cmake_minimum_required(VERSION 3.29)
project(CampusNavigation)

set(CMAKE_CXX_STANDARD 17)

add_executable(CampusNavigation src/main.cpp
        include/LGraph.h
        include/LocationInfo.h
        include/GraphException.h
        include/Algorithm.h
        src/Algorithm.cpp
        src/LGraph.cpp)
