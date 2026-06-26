//
// Created by zincronit on 6/26/26.
//

#ifndef TEST_EXERCISE_BANK_CUSTOMER_HPP
#define TEST_EXERCISE_BANK_CUSTOMER_HPP

#include "CustomerType.hpp"
#include "Account.hpp"

struct Customer
{
    int dni;
    char* name;
    CustomerType type;
    Account* account;
    int accounts_count;
};

#endif //TEST_EXERCISE_BANK_CUSTOMER_HPP
