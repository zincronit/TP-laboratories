//
// Created by zincronit on 6/28/26.
//

#ifndef LAB09_2025_2_FUNCTIONS_HPP
#define LAB09_2025_2_FUNCTIONS_HPP

#include "Utils.hpp"
#include "Structs/List.hpp"

void open_output_file(std::ofstream& fout, const char* filepath);
void open_input_file(std::ifstream& fin, const char* filepath);
void print_line(std::ofstream& fout, int width , char c);
void print_text(std::ofstream& fout, const char* text , int width);
int read_time(std::ifstream& fin, bool read_character);
void print_time(std::ofstream& fout, int time);
char* read_string(std::ifstream& fin, char character);
char* assign_string(char* buffer);


#endif //LAB09_2025_2_FUNCTIONS_HPP
