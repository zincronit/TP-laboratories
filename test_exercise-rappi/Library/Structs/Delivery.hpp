//
// Created by zincronit on 6/14/26.
//

#ifndef TEST_EXERCISE_RAPPI_DELIVERY_HPP
#define TEST_EXERCISE_RAPPI_DELIVERY_HPP

#include "Date.hpp"
#include "Time.hpp"

struct Delivery
{
    Date date{};
    int driver_code{};
    Time duration{};
    char* client_code{};
};
#endif //TEST_EXERCISE_RAPPI_DELIVERY_HPP
