//
// Created by zincronit on 6/15/26.
//


#include <algorithm>

#include "Library/Functions.hpp"

int main()
{
    Doctor* doctors{};
    int doctors_count = 0;

    read_data_specialties_file("Data/specialties_doctors.csv",
                               doctors,
                               doctors_count);

    print_values_Doctors("Reports/doctor_report.txt",
                         doctors,
                         doctors_count);

    sort_doctors(doctors, doctors_count);

    print_values_Doctors("Reports/sort_doctor_report.txt",
                         doctors,
                         doctors_count);

    Attention* attentions{};
    int attentions_count = 0;

    read_date_attentions_file("Data/attentions.csv",
                              attentions,
                              attentions_count);

    print_array_attentions("Reports/attentions_report.txt",
                           attentions,
                           attentions_count);

    print_reports(doctors,
                  doctors_count,
                  attentions,
                  attentions_count);

    return 0;
}
