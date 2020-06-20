cmake_minimum_required(VERSION 3.15)
project(airportCounter)

set(CMAKE_CXX_STANDARD 17)

add_executable(airportCounter main.cpp)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")