cmake_minimum_required(VERSION 4.2)
project(lab10_2026_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab10_2026_1
        main.cpp
        Library/Functions.cpp
        Library/Functions.hpp
        Library/Utils.hpp
        Library/Structs/Date.hpp
        Library/Structs/Time.hpp
        Library/Structs/Code.hpp
        Library/Structs/Attention.hpp
        Library/Structs/Doctor.hpp)
