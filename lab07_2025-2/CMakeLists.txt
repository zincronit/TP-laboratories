cmake_minimum_required(VERSION 4.2)
project(lab07_2025_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab07_2025_2
        main.cpp
        Library/Utils.hpp
        Library/Functions.hpp
        Library/Functions.cpp
        Library/Structs/Reproduction.hpp
        Library/Structs/Time.hpp
        Library/Structs/Category.hpp)
