//
// Created by zincronit on 5/31/26.
//

#include "Library/Functions.hpp"

int main()
{
    //violations_table.txt
    int violation_codes[MAX_VIOLATIONS]{};
    double violation_values[MAX_VIOLATIONS]{};
    int size_violations = 0;

    read_data_violations_table_file("Data/violations_table.txt",
                                    violation_codes,
                                    violation_values,
                                    size_violations);

    print_arrays_violations_table_file("Report/report_violations_table.txt",
                                    violation_codes,
                                    violation_values,
                                    size_violations);

    //commited_violations.txt
    int dnis[MAX_COMMITED_VIOLATIONS]{};
    int oldest_fine_dates[MAX_COMMITED_VIOLATIONS]{};
    int last_paid_fine_dates[MAX_COMMITED_VIOLATIONS]{};
    double total_fine_amounts[MAX_COMMITED_VIOLATIONS]{};
    double paid_fine_amounts[MAX_COMMITED_VIOLATIONS]{};
    double pending_fine_amounts[MAX_COMMITED_VIOLATIONS]{};
    int size_companies=0;

    read_join_data_commited_violations_file("Report/license_plates.txt",
                                             "Data/committed_violations.txt",
                                              violation_codes,
                                              violation_values,
                                             size_violations,
                                              dnis,
                                              oldest_fine_dates,
                                              last_paid_fine_dates,
                                              total_fine_amounts,
                                              paid_fine_amounts,
                                              pending_fine_amounts,
                                              size_companies);
    std::cout<< size_companies;

    print_report("Report/report.txt",
                   dnis,
                   oldest_fine_dates,
                   last_paid_fine_dates,
                   total_fine_amounts,
                   paid_fine_amounts,
                   pending_fine_amounts,
                   size_companies);
    return 0;
}
