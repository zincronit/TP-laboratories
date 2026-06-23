//
// Created by zincronit on 5/30/26.
//

#ifndef LAB06_2025_2_FUNCTIONS_HPP
#define LAB06_2025_2_FUNCTIONS_HPP

#include "Utils.hpp"

void generate_file_link(const char* stream_name, char* file_name, char* link);

void read_data_categories(const char* file_path,
                          char** stream_codes,
                          char** names,
                          int& size);

void report_arrays_categories(const char* file_path,
                              char** stream_codes,
                              char** names,
                              int size);


void read_data_reproductions_file(const char* file_path,
                                  int* dates,
                                  char** channels,
                                  char** codes,
                                  double* rating,
                                  double* drop_off,
                                  int* stream_durations,
                                  int& size);

void print_arrays_reproductions(const char* file_path,
                                int* dates,
                                char** channels,
                                char** codes,
                                double* rating,
                                double* drop_off,
                                int* stream_durations,
                                int size);

void print_report(const char* file_path,
                  const char* file_link,
                  char* stream_code,
                  char* name,
                  int* dates,
                  char** channels,
                  char** codes,
                  double* rating,
                  double* drop_off,
                  int* stream_durations,
                  int size);

#endif //LAB06_2025_2_FUNCTIONS_HPP