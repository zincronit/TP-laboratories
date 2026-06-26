cmake_minimum_required(VERSION 4.2)
project(test_exercise_rappi)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_exercise_rappi
        main.cpp
        Library/Utils.hpp
        Library/Functions.hpp
        Library/Functions.cpp
        Library/Structs/Driver.hpp
        Library/Structs/Date.hpp
        Library/Structs/Time.hpp
        Library/Structs/Delivery.hpp
        Library/Structs/Code.hpp)
