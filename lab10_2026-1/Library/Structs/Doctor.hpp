//
// Created by zincronit on 7/1/26.
//

#ifndef LAB10_2026_1_DOCTOR_HPP
#define LAB10_2026_1_DOCTOR_HPP

#include "Attention.hpp"

struct Doctor
{
    int code;
    char* name;
    char* specialty;
    double rate;
    Attention* attentions;
    int attentions_count;
    double care_revenue;
};

#endif //LAB10_2026_1_DOCTOR_HPP
