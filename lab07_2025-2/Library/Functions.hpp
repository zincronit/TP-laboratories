//
// Created by zincronit on 6/14/26.
//

#ifndef LAB07_2025_2_FUNCTIONS_HPP
#define LAB07_2025_2_FUNCTIONS_HPP

#include "Utils.hpp"
#include "Structs/Category.hpp"

void read_data_categories_file(const char* file_path,
                          Category*& categories,
                          int& size);

void print_categories_values(const char* file_path,
                             Category* categories,
                             int size);

void read_data_reproductions_file(const char* file_path,
                                  Category* categories,
                                  int size);

void update_categories_values(Category* c, int size);

void print_report(const char* file_path,
                  Category* c,
                  int size);

#endif //LAB07_2025_2_FUNCTIONS_HPP
