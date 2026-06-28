//
// Created by zincronit on 6/26/26.
//

#include "Library/Functions.hpp"

int main()
{
    CustomerType* types;
    int num_types = 0;
    read_data_customers_type_file("Data/customers_type.txt",
                                  types,
                                  num_types);

    print_data_customers_type("Reports/customers_type_report.txt",
                              types,
                              num_types);

    Customer* customers;
    int customers_count = 0;

    read_data_customers_file("Data/customers.csv",
                             customers,
                             customers_count,
                             types,
                             num_types);

    print_report("Reports/initial_customers.txt",
                 customers,
                 customers_count,
                 1);

    read_data_accounts_file("Data/accounts.csv",
                            customers,
                            customers_count);

    print_report("Reports/initial_customers_accounts.txt",
                 customers,
                 customers_count,
                 2);

    read_data_transactions_file("Data/transactions.csv",
                                customers,
                                customers_count);

    print_report("Reports/report_customers_accounts.txt",
                 customers,
                 customers_count,
                 3);

    return 0;
}
