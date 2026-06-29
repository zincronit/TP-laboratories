//
// Created by zincronit on 6/28/26.
//

#ifndef LAB09_2025_2_FUNCTIONS_HPP
#define LAB09_2025_2_FUNCTIONS_HPP

#include "Utils.hpp"

void open_file_output(std::ofstream& fout, const char* filepath);
void open_input_file(std::ifstream& fin, const char* filepath);
void print_line(std::ofstream& fout, int width , char c);
void print_text(std::ofstream& fout, const char* text , int width);

#endif //LAB09_2025_2_FUNCTIONS_HPP
