//
// Created by zincronit on 7/1/26.
//

#ifndef LAB10_2026_1_FUNCTIONS_HPP
#define LAB10_2026_1_FUNCTIONS_HPP

#include "Utils.hpp"
#include "Structs/Doctor.hpp"

void open_output_file(std::ofstream& fout, const char* filepath);
void open_input_file(std::ifstream& fin, const char* filepath);
void print_line(std::ofstream& fout, int width , char c);
void print_spaces(std::ofstream& fout, int extra, int width);
void print_text(std::ofstream& fout , const char* text, int width);
char* read_string(std::ifstream& fin, char delimiter);
char* assign_string(const char* buffer);
int read_int(std::ifstream& fin , bool read_character);
double read_double(std::ifstream& fin, bool read_character);
Time read_time(std::ifstream& fin , bool read_character);
Date read_date(std::ifstream& fin , bool read_character);
Code read_code(std::ifstream& fin, bool read_character);
void print_date(std::ofstream& fout, Date d, int width);
void print_time(std::ofstream& fout, Time t, int width);
void print_code(std::ofstream& fout, Code c, int width);


#endif //LAB10_2026_1_FUNCTIONS_HPP
