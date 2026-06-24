//
// Created by zincronit on 5/31/26.
//

#ifndef LAB06_2025_1_FUNCTIONS_HPP
#define LAB06_2025_1_FUNCTIONS_HPP

#include "Utils.hpp"

void open_output_file(std::ofstream& fout, const char* file_path);
void open_input_file(std::ifstream& fin, const char* file_path);

void read_data_violations_table_file(const char* file_path,
                                     int* violation_codes,
                                     double* violation_values,
                                     int& size);

void print_arrays_violations_table_file(const char* file_path,
                                        int* violation_codes,
                                        double* violation_values,
                                        int size);

void read_join_data_commited_violations_file(const char* output_file_path,
                                             const char* input_file_path,
                                             int* violation_codes,
                                             double* violation_values,
                                             int size_violations,
                                             int* dnis,
                                             int* oldest_fine_dates,
                                             int* last_paid_fine_dates,
                                             double* total_fine_amounts,
                                             double* paid_fine_amounts,
                                             double* pending_fine_amounts,
                                             int& size_companies);
void print_report(const char* file_path,
                  int* dnis,
                  int* oldest_fine_dates,
                  int* last_paid_fine_dates,
                  double* total_fine_amounts,
                  double* paid_fine_amounts,
                  double* pending_fine_amounts,
                  int size_companies);

#endif //LAB06_2025_1_FUNCTIONS_HPP