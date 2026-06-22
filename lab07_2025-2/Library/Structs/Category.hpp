//
// Created by zincronit on 6/14/26.
//

#ifndef LAB07_2025_2_CATEGORY_HPP
#define LAB07_2025_2_CATEGORY_HPP
#include "Reproduction.hpp"

struct Category
{
    char* code{};
    char* name{};
    Reproduction* reproductions{};
    int reproductions_count{};
    Time total_duration{};
    double avg_rating{};
};


#endif //LAB07_2025_2_CATEGORY_HPP
