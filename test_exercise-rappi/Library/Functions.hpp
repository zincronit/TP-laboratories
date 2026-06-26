//
// Created by zincronit on 6/14/26.
//

#ifndef TEST_EXERCISE_RAPPI_FUNCTIONS_HPP
#define TEST_EXERCISE_RAPPI_FUNCTIONS_HPP

#include "Utils.hpp"
#include "Structs/Driver.hpp"
#include "Structs/Delivery.hpp"

void read_data_rute_file(const char* file_path,
                         Driver*& driver,
                         int& size);

void print_drivers_report(const char* file_path,
                          const Driver* d,
                          int size);

void sort_drivers(Driver* drivers, int size);

void read_data_deliveries_file(const char* file_path,
                               Delivery*& delivery,
                               int& size);

void sort_deliveries(Delivery* delivery, int size);

void print_report(const char* file_path,
                  const Driver* driver,
                  int size_driver,
                  const Delivery* delivery,
                  int size_delivery);

#endif //TEST_EXERCISE_RAPPI_FUNCTIONS_HPP
