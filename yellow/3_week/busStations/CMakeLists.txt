cmake_minimum_required(VERSION 3.14)
project(busStations)

set(CMAKE_CXX_STANDARD 17)

add_executable(busStations main.cpp query.cpp responses.cpp bus_manager.cpp)