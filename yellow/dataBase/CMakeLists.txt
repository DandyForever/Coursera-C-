cmake_minimum_required(VERSION 3.14)
project(dataBase)

set(CMAKE_CXX_STANDARD 14)

add_executable(dataBase main.cpp token.cpp condition_parser.cpp
        condition_parser_test.cpp date.cpp database.cpp node.cpp
        test_runner.cpp empty_node.cpp date_comparison_node.cpp
        event_comparison_node.cpp logical_operation_node.cpp)