cmake_minimum_required(VERSION 3.21)
project(Mini_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Mini_Project main.cpp CMax3SatProblem.cpp CMax3SatProblem.h CGAOptimizer.h CGAIndividual.h Problem.h)
