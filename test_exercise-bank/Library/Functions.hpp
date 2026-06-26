//
// Created by zincronit on 6/26/26.
//

#ifndef TEST_EXERCISE_BANK_FUNCTIONS_HPP
#define TEST_EXERCISE_BANK_FUNCTIONS_HPP

#include "Utils.hpp"
#include "Structs/Customer.hpp"

void read_data_customers_type_file(const char* file_path,
                                   CustomerType*& c,
                                   int& size);

void print_data_customers_type(const char* file_path,
                               CustomerType* c,
                               int size);


#endif //TEST_EXERCISE_BANK_FUNCTIONS_HPP
