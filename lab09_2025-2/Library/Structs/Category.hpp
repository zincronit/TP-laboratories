//
// Created by zincronit on 6/29/26.
//

#ifndef LAB09_2025_2_CATEGORY_HPP
#define LAB09_2025_2_CATEGORY_HPP

struct Category
{
    char* code;
    char* name;
    char* description;
    char* channel_max_duration;
    int max_duration;
    int total_duration;
    double arr_drop_off[20];
    int reproductions_count;
    double avg_drop_off;
};

#endif //LAB09_2025_2_CATEGORY_HPP
