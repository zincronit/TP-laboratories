//
// Created by zincronit on 6/15/26.
//

#ifndef LAB07_2026_1_FUNCTIONS_HPP
#define LAB07_2026_1_FUNCTIONS_HPP

#include "Utils.hpp"
#include "Structs/Doctor.hpp"

void read_data_specialties_file(const char* file_path,
                                Doctor*& d,
                                int& count);

void print_values_Doctors(const char* file_path,
                          Doctor* d,
                          int count);

void sort_doctors(Doctor* d, int count);

void read_date_attentions_file(const char* file_path,
                               Attention*& a,
                               int& count);

void print_array_attentions(const char* file_path,
                            Attention* a,
                            int count);

void generate_report(const char* file_path,
                     Doctor& d,
                     Attention* a,
                     int attentions_count);

void print_reports(Doctor* d,
                   int doctors_count,
                   Attention* a,
                   int attentions_count);

#endif //LAB07_2026_1_FUNCTIONS_HPP
