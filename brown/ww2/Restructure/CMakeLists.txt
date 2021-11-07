cmake_minimum_required(VERSION 3.20)
project(Restructure)

set(CMAKE_CXX_STANDARD 17)

add_executable(Restructure main.cpp stats_aggregator.cpp stats_aggregator.h stats_aggregator_test.cpp)
