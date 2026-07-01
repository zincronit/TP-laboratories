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

    print_report("Reports/first_report.txt", list, true);

    read_data_reproductions_file("Data/stream_reproductions.csv",
                                 list);

    calculate_avg_drop_off(list);

    print_report("Reports/final_report.txt", list, false);

    return 0;
}
