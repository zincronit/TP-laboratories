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

char* read_string(std::ifstream& fin, char delimiter)
{
    char buffer[MAX_LENGTH];
    char* string = nullptr;
    fin.getline(buffer, MAX_LENGTH, delimiter);
    if (fin.eof()) return nullptr;
    string = new char[std::strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

int read_int(std::ifstream& fin)
{
    int value = 0;
    fin >> value;
    fin.get();
    return value;
}

double read_double(std::ifstream& fin)
{
    double value = 0;
    fin >> value;
    return value;
}

void read_driver(std::ifstream& fin, Driver& d)
{
    // 7845,QUISPE ROJAS MARIO ALBERTO,35.50,
    d.code = read_int(fin);
    d.name = read_string(fin, ',');
    d.rate = read_double(fin);
}

void read_data_rute_file(const char* file_path,
                         Driver*& driver,
                         int& size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    driver = new Driver[MAX_DRIVERS]{};
    int location_code = 0;
    char c;

    while (true)
    {
        char* location_name = nullptr;
        //301,LIMA NORTE,7845,QUISPE ROJAS MARIO ALBERTO,35.50,6123,TORRES VEGA ANA LUCIA,42.80
        fin >> location_code;
        if (fin.eof()) break;
        fin.ignore();
        location_name = read_string(fin, ',');
        while (true)
        {
            // 7845,QUISPE ROJAS MARIO ALBERTO,35.50,
            read_driver(fin, driver[size]);
            driver[size].route_code = location_code;
            driver[size].route_name = location_name;
            size++;
            fin.get(c);
            if (c == '\n' or fin.eof()) break;
        }
    }
    fin.close();
}

void print_drivers_report(const char* file_path,
                          const Driver* d,
                          int size)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    fout << "DRIVERS" << std::endl;
    print_line(fout, 200, '=');
    int width = 200 / 5;
    print_text(fout, "CODE", width);
    print_text(fout, "NAME", width);
    print_text(fout, "ROUTE CODE", width);
    print_text(fout, "ROUTE NAME", width);
    print_text(fout, "DRIVER RATE", width);
    fout << std::fixed << std::setprecision(2) << std::endl;
    for (int i = 0; i < size; i++)
    {
        fout << std::setw(width) << d[i].code;
        print_text(fout, d[i].name, width);
        fout << std::setw(width) << d[i].route_code;
        print_text(fout, d[i].route_name, width);
        fout << std::setw(width) << d[i].rate << std::endl;
    }
    fout.close();
}

void swap_driver(Driver& d1, Driver& d2)
{
    Driver temp;
    temp = d1;
    d1 = d2;
    d2 = temp;
}

void sort_drivers(Driver* drivers, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (std::strcmp(drivers[i].name, drivers[j].name) > 0)
            {
                swap_driver(drivers[j], drivers[i]);
            }
        }
    }
}

// void read_delivery_date(std::ifstream& fin, Delivery& d)
// {
//     char c;
//     fin >> d.date.day ;
//     if (fin.eof()) return;
//     fin >> c >> d.date.month >> c >> d.date.year;
//     d.date.format= d.date.year*10000 + d.date.month*100 + d.date.day;
// }
//
// void read_delivery_time(std::ifstream& fin , Delivery& d)
// {
//     char c;
//     fin >> d.duration.hours >> c >> d.duration.minutes >> c >> d.duration.seconds ;
//     fin.ignore();
//     d.duration.total_seconds =d.duration.hours*3600 + d.duration.minutes * 60 + d.duration.seconds;
// }

int read_time(std::ifstream& fin)
{
    int hh, mm, ss;
    char c;
    fin >> hh >> c >> mm >> c >> ss;
    fin.ignore();
    return hh * 3600 + mm * 60 + ss;
}

void read_delivery(std::ifstream& fin, Delivery& d, int date)
{
    // 102,08:15:00,CLI-45-8912,10:30:20,7845,
    int start_time, end_time, duration;
    start_time = read_time(fin);
    d.client_code = read_string(fin, ',');
    end_time = read_time(fin);
    fin>> d.driver_code;
    duration = end_time - start_time;
    if (end_time < start_time) duration = 24 * 3600 - start_time + end_time;
    d.date.year = date / 10000;
    d.date.month = date % 10000 / 100;
    d.date.day = date % 100;
    d.date.format = date;
    d.duration.hours = duration / 3600;
    d.duration.minutes = duration % 3600 / 60;
    d.duration.seconds = duration % 60;
    d.duration.total_seconds = duration;

}

void read_data_deliveries_file(const char* file_path,
                               Delivery*& delivery,
                               int& size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    delivery = new Delivery[MAX_DELIVERIES]{};
    int dd, mm, yy, date, trash;
    char c;
    while (true)
    {
        // 1/04/2023,102,08:15:00,CLI-45-8912,10:30:20,7845,
        fin >> dd;
        if (fin.eof()) break;
        fin >> c >> mm >> c >> yy;
        fin.ignore();
        date = yy * 10000 + mm * 100 + dd;
        while (true)
        {
            // 102,08:15:00,CLI-45-8912,10:30:20,7845,
            fin >> trash;
            fin.ignore();
            read_delivery(fin, delivery[size], date);
            size++;
            fin.get(c);
            if (c == '\n' or fin.eof()) break;
        }
    }
    fin.close();
}

void swap_delivery(Delivery& d1, Delivery& d2)
{
    Delivery temp;
    temp = d1;
    d1 = d2;
    d2 = temp;
}

void sort_deliveries(Delivery* delivery, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (delivery[i].date.format < delivery[j].date.format or
                (delivery[i].date.format == delivery[j].date.format and
                    std::strcmp(delivery[i].client_code, delivery[j].client_code) < 0))
            {
                swap_delivery(delivery[i], delivery[j]);
            }
        }
    }
}

void print_title(std::ofstream& fout, const char* title)
{
    fout << std::right << std::setw((LINE_WIDTH + std::strlen(title)) / 2) << title << std::endl;
    print_line(fout, LINE_WIDTH, '=');
}

void print_static_header(std::ofstream& fout, int i, int width)
{
    fout << "DRIVER: " << std::setfill('0') << std::right << std::setw(2) << i+1 << std::endl;
    fout << std::setfill(' ');
    print_text(fout, "CODE", width);
    print_text(fout, "NAME", width);
    print_text(fout, "RATE", width);
    print_text(fout, "ROUTE CODE", width);
    print_text(fout, "ROUTE NAME", width);
    fout << std::endl;
}

void print_spaces(std::ofstream& fout, int extra, int width)
{
    for (int i = 0; i < width - extra; i++) fout.put(' ');
}

void print_values_driver(std::ofstream& fout, const Driver* driver, int i, int width)
{
    fout << std::setw(width) << driver[i].code;
    print_text(fout, driver[i].name, width);
    fout << "S/." << driver[i].rate;
    print_spaces(fout, 7, width);
    fout << std::setw(width) << driver[i].route_code;
    print_text(fout, driver[i].route_name, width);
    fout << std::endl;
    print_line(fout, LINE_WIDTH, '=');
}

void print_second_header(std::ofstream& fout, int width)
{
    fout << "DELIVERIES" << std::endl;
    fout << std::setw(3) << ' ';
    print_text(fout, "DATE", width);
    print_text(fout, "CUSTOMER", width);
    print_text(fout, "DELIVERY DELAY", width);
    print_text(fout, "PAYMENT", width);
    fout << std::endl;
}

void print_dynamic_part(std::ofstream& fout,
                        const Driver& driver,
                        const Delivery* delivery,
                        int size_delivery,
                        int width)
{
    int i = 0;
    for (int j = 0; j < size_delivery; j++)
    {
        if (driver.code == delivery[j].driver_code)
        {
            fout << std::right << std::setfill('0') << std::setw(2) << i << ')';
            fout << std::setw(2) << delivery[j].date.day << '/'
                << std::setw(2) << delivery[j].date.month << '/'
                << std::setw(4) << delivery[j].date.year << std::setfill(' ') << std::left ;
            print_spaces(fout, 10, width);
            print_text(fout, delivery[j].client_code, width);
            fout << std::right << std::setfill('0') << std::setw(2) << delivery[j].duration.hours << ':'
            << std::setw(2) << delivery[j].duration.minutes << ':'
            << std::setw(2) << delivery[j].duration.seconds << ' ' << std::setfill(' ') << std::left;
            print_spaces(fout, 8, width);
            fout << "S/." << driver.rate*delivery[j].duration.total_seconds/3600.0 << std::endl;
            i++;
        }
    }
}


void print_report(const char* file_path,
                  const Driver* driver,
                  int size_driver,
                  const Delivery* delivery,
                  int size_delivery)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    print_title(fout, "REPORT RAPPI");
    int width = LINE_WIDTH / COLUMNS;
    fout << std::fixed << std::setprecision(2);
    for (int i = 0; i < size_driver; i++)
    {
        print_static_header(fout, i, width);
        print_values_driver(fout, driver, i, width);
        print_second_header(fout, width);
        print_dynamic_part(fout, driver[i] ,delivery, size_delivery, width);
    }

    fout.close();
}
