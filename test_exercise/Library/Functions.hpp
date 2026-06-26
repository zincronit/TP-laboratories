//
// Created by zincronit on 5/12/26.
//

#ifndef TEST_EXERCISE_FUNCTIONS_HPP
#define TEST_EXERCISE_FUNCTIONS_HPP

#include "Utils.hpp"

void open_output_file(std::ofstream& fout, const char* file_path);
void open_input_file(std::ifstream& fin, const char* file_path);

void print_report(const char* output_path,
                  const char* courses_path,
                  const char* professor_path,
                  const char* sessions_path);

#endif //TEST_EXERCISE_FUNCTIONS_HPP
