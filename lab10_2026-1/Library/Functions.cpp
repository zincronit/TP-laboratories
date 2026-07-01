#include "Functions.hpp"

void open_output_file(std::ofstream& fout, const char* filepath)
{
    fout.open(filepath);
    if (not fout.is_open())
    {
        std::cout << "Error opening file " << filepath << std::endl;
        std::exit(1);
    }
}

void open_input_file(std::ifstream& fin, const char* filepath)
{
    fin.open(filepath);
    if (not fin.is_open())
    {
        std::cout << "Error opening file " << filepath << std::endl;
        std::exit(1);
    }
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

void print_text(std::ofstream& fout, const char* text, int width)
{
    fout << std::left << std::setw(width) << text;
}

char* read_string(std::ifstream& fin, char delimiter)
{
    char buffer[TEXT_LENGTH];
    char* string = nullptr;
    fin.getline(buffer, TEXT_LENGTH, delimiter);
    if (fin.eof()) return nullptr;
    string = new char[std::strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

char* assign_string(const char* buffer)
{
    char* string = new char[strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

int read_int(std::ifstream& fin, bool read_character)
{
    int value;
    fin >> value;
    if (read_character) fin.get();
    return value;
}

double read_double(std::ifstream& fin, bool read_character)
{
    double value;
    fin >> value;
    if (read_character) fin.get();
    return value;
}

Time read_time(std::ifstream& fin, bool read_character)
{
    Time t;
    char c;
    fin >> t.hour >> c >> t.minute >> c >> t.second;
    t.total_sec = t.hour * 3600 + t.minute * 60 + t.second;
    return t;
}

Date read_date(std::ifstream& fin, bool read_character)
{
    Date d;
    char c;
    fin >> d.year >> c >> d.month >> c >> d.day;
    d.format = d.year * 10000 + d.month * 100 + d.day;
    return d;
}

Code read_code(std::ifstream& fin, bool read_character)
{
    Code c;
    char f;
    fin >> c.value1 >> f >> c.value2 >> f >> c.value3;
    return c;
}

void print_date(std::ofstream& fout, Date d, int width)
{
    fout << std::right << std::setfill('0') << std::setw(2) << d.day << '/'
        << std::setw(2) << d.month << '/'
        << std::setw(4) << d.year << std::left << std::setfill(' ');
    print_spaces(fout, 10, width);
}

void print_time(std::ofstream& fout, Time t, int width)
{
    t.hour = t.total_sec / 3600;
    t.minute = t.total_sec % 3600 / 60;
    t.second = t.total_sec % 60;
    fout << std::right << std::setfill('0') << std::setw(2) << t.hour << ':'
        << std::setw(2) << t.minute << ':'
        << std::setw(2) << t.second << std::left << std::setfill(' ');
    print_spaces(fout, 8, width);
}

void print_code(std::ofstream& fout, Code c, int width)
{
    fout << c.value1 << '-' << c.value2 << '-' << c.value3 ;
    print_spaces(fout, 9, width);
}
