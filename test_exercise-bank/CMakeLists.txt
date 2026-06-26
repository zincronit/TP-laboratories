cmake_minimum_required(VERSION 4.2)
project(test_exercise_bank)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_exercise_bank
        Library/Utils.hpp
        Library/Functions.hpp
        main.cpp
        Library/Functions.cpp
        Library/Structs/CustomerType.hpp
        Library/Structs/Transaction.hpp
        Library/Structs/Account.hpp
        Library/Structs/Customer.hpp)
