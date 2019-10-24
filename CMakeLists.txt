cmake_minimum_required(VERSION 3.15)
project(MyMaxSat)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

add_executable(MyMaxSat main.cpp
        data/variable.hpp data/clause.hpp data/formula.hpp
        algorithm/randomizedSolver.hpp
        algorithm/derandomizedSolver.hpp
        config.h algorithm/LPSolver.hpp)

# Find Gurobi
find_package(GUROBI REQUIRED)
if(GUROBI_FOUND)
    MESSAGE( STATUS "GUROBI_INCLUDE_DIRS = ${GUROBI_INCLUDE_DIRS}.")
    MESSAGE( STATUS "GUROBI_LIBRARIES = ${GUROBI_LIBRARIES}.")
    include_directories(SYSTEM ${GUROBI_INCLUDE_DIRS})
    target_link_libraries (MyMaxSat ${GUROBI_LIBRARIES})
endif()