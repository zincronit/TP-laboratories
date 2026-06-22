//
// Created by zincronit on 6/14/26.
//

#include "Library/Functions.hpp"

int main()
{
    Category* categories{};
    int categories_count = 0;

    read_data_categories_file("Data/categories.csv",
                              categories,
                              categories_count);

    print_categories_values("Reports/categories_report.txt",
                            categories,
                            categories_count);

    read_data_reproductions_file("Data/reproductions.csv",
                                 categories,
                                 categories_count);

    update_categories_values( categories, categories_count);

    print_report("Reports/report.txt",
                   categories,
                  categories_count);

    return 0;
}
