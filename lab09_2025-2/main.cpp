//
// Created by zincronit on 6/28/26.
//

#include "Library/Functions.hpp"

int main()
{
    List list;
    read_data_categories_file("Data/categories.csv",
                              list);

    print_data_categories("Reports/test_report.txt",
                          list);

    print_report("Reports/first_report.txt", list,true);

    return 0;
}
