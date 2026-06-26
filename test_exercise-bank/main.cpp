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



    return 0;
}
