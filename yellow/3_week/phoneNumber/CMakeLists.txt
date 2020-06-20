cmake_minimum_required(VERSION 3.14)
project(phoneNumber)

set(CMAKE_CXX_STANDARD 14)

add_executable(phoneNumber main.cpp phone_number.cpp unitTestFramework.cpp tests.cpp)