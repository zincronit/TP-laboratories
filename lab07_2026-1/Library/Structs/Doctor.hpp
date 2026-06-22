//
// Created by zincronit on 6/15/26.
//

#ifndef LAB07_2026_1_DOCTOR_HPP
#define LAB07_2026_1_DOCTOR_HPP

#include "Specialty.hpp"
#include "Attention.hpp"

struct Doctor
{
    char* name{};
    double rate{};
    int code{};
    Specialty specialty{};
};


#endif //LAB07_2026_1_DOCTOR_HPP
