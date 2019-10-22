cmake_minimum_required(VERSION 3.15)
project(MyMaxSat)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyMaxSat main.cpp
        data/variable.hpp data/clause.hpp data/formula.hpp
        algorithm/randomizedSolver.hpp
        algorithm/derandomizedSolver.hpp
        config.h)