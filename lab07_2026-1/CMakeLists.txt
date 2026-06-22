cmake_minimum_required(VERSION 4.2)
project(lab07_2026_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab07_2026_1
        main.cpp
        Library/Utils.hpp
        Library/Functions.hpp
        Library/Functions.cpp
        Library/Structs/Doctor.hpp
        Library/Structs/Specialty.hpp
        Library/Structs/Attention.hpp
        Library/Structs/Time.hpp
        Library/Structs/Date.hpp
        Library/Structs/Code.hpp)
