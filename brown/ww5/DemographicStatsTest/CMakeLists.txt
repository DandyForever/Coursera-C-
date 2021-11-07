cmake_minimum_required(VERSION 3.20)
project(DemographicStatsTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(DemographicStatsTest main.cpp)
add_executable(DemographicStatsSolutionA solutionA.cpp)
add_executable(DemographicStatsSolutionB solutionB.cpp)
add_executable(DemographicStatsBug1 bug1.cpp)
add_executable(DemographicStatsBug2 bug2.cpp)
add_executable(DemographicStatsBug3 bug3.cpp)
add_executable(DemographicStatsBug4 bug4.cpp)
add_executable(DemographicStatsBug5 bug5.cpp)
add_executable(DemographicStatsBug6 bug6.cpp)
