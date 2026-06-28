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

void read_data_customers_file(const char* file_path,
                              Customer*& c,
                              int& count,
                              CustomerType* t,
                              int size);

void print_report(const char* file_path,
                  Customer* c,
                  int count,
                  int report_type);

void read_data_accounts_file(const char* file_path,
                             Customer* c,
                             int count);

void read_data_transactions_file(const char* file_path,
                                 Customer* c,
                                 int count);

#endif //TEST_EXERCISE_BANK_FUNCTIONS_HPP
