//
// Created by zincronit on 6/28/26.
//

#ifndef LAB09_2025_2_FUNCTIONS_HPP
#define LAB09_2025_2_FUNCTIONS_HPP

#include "Utils.hpp"
#include "Structs/List.hpp"

void open_output_file(std::ofstream& fout, const char* filepath);
void open_input_file(std::ifstream& fin, const char* filepath);
void print_line(std::ofstream& fout, int width, char c);
void print_text(std::ofstream& fout, const char* text, int width);
int read_time(std::ifstream& fin, bool read_character);
void print_time(std::ofstream& fout, int time);
char* read_string(std::ifstream& fin, char character);
char* assign_string(char* buffer);

void read_data_categories_file(const char* filepath,
                               List& list);
void print_data_categories(const char* filepath,
                           List& list);
void print_report(const char* filepath, struct List& list, bool first_part);

void read_data_reproductions_file(const char* filepath,
                                  struct List& list);

void calculate_avg_drop_off(struct List& list);


#endif //LAB09_2025_2_FUNCTIONS_HPP
