//
// Created by zincronit on 6/15/26.
//

#ifndef LAB07_2026_1_ATTENTION_HPP
#define LAB07_2026_1_ATTENTION_HPP

#include "Time.hpp"
#include "Date.hpp"
#include "Code.hpp"


struct Attention
{
    Date date{};
    Code patient_code{};
    Time duration{};
    double payment{};
    int doctor_code{};
};

#endif //LAB07_2026_1_ATTENTION_HPP
