//
// Created by zincronit on 6/26/26.
//

#ifndef TEST_EXERCISE_BANK_ACCOUNT_HPP
#define TEST_EXERCISE_BANK_ACCOUNT_HPP

#include "Transaction.hpp"

struct Account
{
    int account_no;
    double initial_balance;
    double final_balance;
    int withdrawal_count;
    int deposit_count;
    char* status;
    Transaction* transactions;
    int transactions_count;
};

#endif //TEST_EXERCISE_BANK_ACCOUNT_HPP
