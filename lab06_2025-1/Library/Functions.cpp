#include "Functions.hpp"

void open_output_file(std::ofstream& fout, const char* file_path)
{
    fout.open(file_path);
    if (not fout.is_open())
    {
        std::cout << "Error opening file " << file_path << std::endl;
        std::exit(1);
    }
}

void open_input_file(std::ifstream& fin, const char* file_path)
{
    fin.open(file_path);
    if (not fin.is_open())
    {
        std::cout << "Error opening file " << file_path << std::endl;
        std::exit(1);
    }
}

void print_text(std::ofstream& fout, const char* text, int width)
{
    fout << std::left << std::setw(width) << text;
}

void print_line(std::ofstream& fout, int width, char c)
{
    for (int i = 0; i < width; i++) fout.put(c);
    fout << std::endl;
}

void print_spaces(std::ofstream& fout, int extra, int width)
{
    for (int i = 0; i < width - extra; i++) fout.put(' ');
}

int read_date(std::ifstream& fin)
{
    int dd, mm, yy;
    char c;
    fin >> dd >> c >> mm >> c >> yy;
    return yy * 10000 + mm * 100 + dd;
}

void print_date(std::ofstream& fout, int date, int width)
{
    fout << std::right << std::setfill('0') << std::setw(2) << date % 100 << '/'
        << std::setw(2) << date % 10000 / 100 << '/'
        << std::setw(4) << date / 10000 << std::left << std::setfill(' ');
    print_spaces(fout, 10, width);
}

// void insertion_sorted(int array , int value , int& size)
// {
//     int i=size-1;
//     while (i >= 0 and array < size)
//     {
//         i--;
//     }
//     violation_values=
// }

void read_data_violations_table_file(const char* file_path,
                                     int* violation_codes,
                                     double* violation_values,
                                     int& size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    int violation_code;
    double violation_value;
    while (true)
    {
        fin >> violation_code;
        if (fin.eof()) break;
        fin >> violation_value;
        int i = size - 1;
        while (i >= 0 and violation_codes[i] > violation_code)
        {
            violation_codes[i + 1] = violation_codes[i];
            violation_values[i + 1] = violation_values[i];
            i--;
        }
        violation_codes[i + 1] = violation_code;
        violation_values[i + 1] = violation_value;
        size++;
        fin.ignore(200, '\n');
    }
    fin.close();
}

void print_arrays_violations_table_file(const char* file_path,
                                        int* violation_codes,
                                        double* violation_values,
                                        int size)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    fout << "Arrays violations_table.txt" << std::endl;
    print_line(fout, 60, '=');
    int width = 30;
    print_text(fout, "VIOLATION CODE", width);
    print_text(fout, "VIOLATION VALUE", width);
    fout << std::endl;
    print_line(fout, 60, '-');
    fout << std::fixed << std::setprecision(2);
    for (int i = 0; i < size; i++)
    {
        fout << std::setw(width) << violation_codes[i] << violation_values[i] << std::endl;
    }
    fout.close();
}

int search_binary(int* array, int value, int size)
{
    int left = 0, right = size - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (array[mid] == value) return mid;
        if (array[mid] < value) left = mid + 1;
        if (array[mid] > value) right = mid - 1;
    }
    return NOT_FOUND;
}

void insertion_sort(double* violation_values,
                    int* dnis,
                    int* oldest_fine_dates,
                    int* last_paid_fine_dates,
                    double* total_fine_amounts,
                    double* paid_fine_amounts,
                    double* pending_fine_amounts,
                    int& size_companies,
                    int index,
                    int violation_date,
                    int paid_date,
                    int dni)
{
    int i = size_companies - 1;
    while (i >= 0 and dnis[i] > dni)
    {
        dnis[i + 1] = dnis[i];
        oldest_fine_dates[i + 1] = oldest_fine_dates[i];
        last_paid_fine_dates[i + 1] = last_paid_fine_dates[i];
        total_fine_amounts[i + 1] = total_fine_amounts[i];
        paid_fine_amounts[i + 1] = paid_fine_amounts[i];
        pending_fine_amounts[i + 1] = pending_fine_amounts[i];
        i--;
    }
    dnis[i + 1] = dni;
    oldest_fine_dates[i + 1] = violation_date;
    last_paid_fine_dates[i + 1] = paid_date;
    total_fine_amounts[i + 1] = violation_values[index];
    if (violation_date != 0) paid_fine_amounts[i + 1] = violation_values[index];
    pending_fine_amounts[i + 1] = total_fine_amounts[i + 1] - paid_fine_amounts[i + 1];
    size_companies++;
}

void update_array(double* violation_values,
                  int* oldest_fine_dates,
                  int* last_paid_fine_dates,
                  double* total_fine_amounts,
                  double* paid_fine_amounts,
                  double* pending_fine_amounts,
                  int index,
                  int violation_date,
                  int paid_date,
                  int local_index)
{
    if (oldest_fine_dates[local_index] > violation_date) oldest_fine_dates[local_index] = violation_date;
    if (last_paid_fine_dates[local_index] < paid_date) last_paid_fine_dates[local_index] = paid_date;
    total_fine_amounts[local_index] += violation_values[index];
    if (paid_date != 0) paid_fine_amounts[local_index] += violation_values[index];
    pending_fine_amounts[local_index] = total_fine_amounts[local_index] - paid_fine_amounts[local_index];
}

void read_join_data_commited_violations_file(const char* output_file_path,
                                             const char* input_file_path,
                                             int* violation_codes,
                                             double* violation_values,
                                             int size_violations,
                                             int* dnis,
                                             int* oldest_fine_dates,
                                             int* last_paid_fine_dates,
                                             double* total_fine_amounts,
                                             double* paid_fine_amounts,
                                             double* pending_fine_amounts,
                                             int& size_companies)
{
    std::ofstream fout;
    std::ifstream fin;
    open_output_file(fout, output_file_path);
    open_input_file(fin, input_file_path);
    int violation_date = 0, dni = 0, violation_code = 0, index;
    char license_plate[15]{}, c;
    while (true)
    {
        int paid_date = 0, local_index;;
        // 1/8/2020       M510-956      86429854   2060      P   2/10/2020
        violation_date = read_date(fin);
        if (fin.eof()) break;
        fin >> std::ws;
        fin >> license_plate >> dni;
        fout << dni << ' ' << license_plate << std::endl;
        fin >> violation_code >> std::ws;
        index = search_binary(violation_codes, violation_code, size_violations);
        // if ( index == NOT_FOUND)
        if (fin.peek() == 'P')
        {
            fin >> c;
            paid_date = read_date(fin);
        }
        local_index = search_binary(dnis, dni, size_companies);
        if (local_index == NOT_FOUND)
        {
            insertion_sort(violation_values,
                           dnis,
                           oldest_fine_dates,
                           last_paid_fine_dates,
                           total_fine_amounts,
                           paid_fine_amounts,
                           pending_fine_amounts,
                           size_companies,
                           index,
                           violation_date,
                           paid_date,
                           dni);
        }
        else
        {
            update_array(violation_values,
                         oldest_fine_dates,
                         last_paid_fine_dates,
                         total_fine_amounts,
                         paid_fine_amounts,
                         pending_fine_amounts,
                         index,
                         violation_date,
                         paid_date,
                         local_index);
        }
    }
    fin.close();
    fout.close();
}

void get_license_plate(const char* license_plate_list, int number, char* license_plate)
{
    if ((std::strlen(license_plate_list) + 1) / 9 < number) return;
    std::strncpy(license_plate, &license_plate_list[number * 9], 8);
    license_plate[8] = '\0';
}

void add_license_plate(char* license_plate_list, const char* license_plate)
{
    for (int i = 1; i <= (std::strlen(license_plate_list) + 1) / 9; i++)
    {
        char string[15]{};
        get_license_plate(license_plate_list, i - 1, string);
        if (std::strcmp(string, license_plate) == 0) return;
    }
    if (std::strlen(license_plate_list) > 0)std::strcat(license_plate_list, "/");
    std::strcat(license_plate_list, license_plate);
}

void print_title(std::ofstream& fout)
{
    fout << std::right << std::setw((LINE_WIDTH + 25) / 2) << "MINISTERIO DE TRANSPORTES" << std::endl;
    fout << std::right << std::setw((LINE_WIDTH + 23) / 2) << "LISTADO DE INFRACCIONES" << std::endl;
    print_line(fout, LINE_WIDTH, '=');
}

void print_headers(std::ofstream& fout)
{
    int width = LINE_WIDTH / COLUMNS;
    fout << std::setw(4 * width + 3) << ' ';
    print_text(fout, "MULTA MAS", width - 2);
    print_text(fout, "ULTIMA MULTA", width);
    print_text(fout, "TOTAL EN", width - 3);
    print_text(fout, "MULTAS", width - 2);
    print_text(fout, "MULTAS", width);
    fout << std::endl;
    fout << "   No.  ";
    print_text(fout, "DNI", width - 5);
    print_text(fout, "PLACAS", 3 * width);
    print_text(fout, "ANTIGUA", width - 2);
    print_text(fout, "PAGADA", width);
    print_text(fout, "MULTAS", width - 3);
    print_text(fout, "PAGADA", width - 4);
    print_text(fout, "PENDIENTES", width);
    fout << std::endl;
}

void get_license_plate_list(const char* file_path, int DNI, char* license_plate_list)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    fin.clear();
    fin.seekg(0, std::ios::beg);
    char license_plate[10]{};
    int dni = 0;
    while (true)
    {
        fin >> dni;
        if (fin.eof()) break;
        if (DNI != dni)
        {
            fin.ignore(20, '\n');
            continue;
        }
        fin >> std::ws >> license_plate;
        add_license_plate(license_plate_list, license_plate);
    }
    fin.close();
}

void print_report(const char* file_path,
                  int* dnis,
                  int* oldest_fine_dates,
                  int* last_paid_fine_dates,
                  double* total_fine_amounts,
                  double* paid_fine_amounts,
                  double* pending_fine_amounts,
                  int size_companies)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    print_title(fout);
    print_headers(fout);
    int width = LINE_WIDTH / COLUMNS;
    double global_fine_amount = 0.0, global_pending_fine_amount = 0.0, global_paid_fine_amount = 0.0;
    fout << std::fixed << std::setprecision(2);
    for (int i = 0; i < size_companies; i++)
    {
        global_fine_amount += total_fine_amounts[i];
        global_paid_fine_amount += paid_fine_amounts[i];
        global_pending_fine_amount += pending_fine_amounts[i];
        char license_plate_list[100]{};
        get_license_plate_list("Report/license_plates.txt", dnis[i], license_plate_list);
        fout << "   " << std::right << std::setfill('0') << std::setw(2) << i + 1
            << std::left << std::setfill(' ') << ")  "
            << std::setw(width - 5) << dnis[i] << std::setw(3 * width) << license_plate_list;
        print_date(fout, oldest_fine_dates[i], width - 2);
        print_date(fout, last_paid_fine_dates[i], width);
        fout << std::setw(width - 3) << total_fine_amounts[i]
            << std::setw(width - 3) << paid_fine_amounts[i]
            << std::setw(width - 3) << pending_fine_amounts[i] << std::endl;
    }
    print_line(fout, LINE_WIDTH, '=');
    fout << "   TOTALES:" << std::right << std::setw(6 * width-1) << global_fine_amount
        << std::setw(width-3) << global_paid_fine_amount << std::setw(width-3) << global_pending_fine_amount << std::endl;
    print_line(fout, LINE_WIDTH, '=');
    fout.close();
}
