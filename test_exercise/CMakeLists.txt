cmake_minimum_required(VERSION 4.1)
project(test_exercise)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_exercise
        main.cpp
        Library/Functions.cpp
        Library/Functions.hpp
        Library/Utils.hpp)
