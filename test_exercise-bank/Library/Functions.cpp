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

void print_line(std::ofstream& fout, int width, char c)
{
    for (int i = 0; i < width; i++) fout.put(c);
    fout << std::endl;
}

void print_text(std::ofstream& fout, const char* text, int width)
{
    fout << std::left << std::setw(width) << text;
}

void print_spaces(std::ofstream& fout, int extra, int width)
{
    for (int i = 0; i < width - extra; i++) fout.put(' ');
}

char* read_string(std::ifstream& fin, char delimiter)
{
    char buffer[TEXT_LENGTH];
    char* string = nullptr;
    fin.getline(buffer,TEXT_LENGTH, delimiter);
    if (fin.eof()) return string;
    string = new char[std::strlen(buffer + 1)];
    strcpy(string, buffer);
    return string;
}

char* assign_string(char* buffer)
{
    char* string = new char[std::strlen(buffer + 1)];
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

char read_char(std::ifstream& fin, bool read_character)
{
    char value;
    fin >> value;
    if (read_character) fin.get();
    return value;
}

void read_static_string(std::ifstream& fin, char* string, char delimiter)
{
    fin.getline(string, TEXT_LENGTH, delimiter);
}

void read_data_customers_type_file(const char* file_path,
                                   CustomerType*& c,
                                   int& size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    c = new CustomerType[MAX_CUSTOMERS_TYPE]{};
    char type;
    while (true)
    {
        // A  Cliente preferente
        type = read_char(fin, true);
        if (fin.eof()) break;
        fin >> std::ws;
        c[size].description = read_string(fin, '\n');
        c[size].type = type;
        size++;
    }
    fin.close();
}

void print_data_customers_type(const char* file_path,
                               CustomerType* c,
                               int size)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    fout << "CUSTOMERS TYPE" << std::endl;
    print_line(fout, 60, '=');
    int width = 60 / 4;
    print_text(fout, "TYPE", width);
    print_text(fout, "DESCRIPTION", size);
    fout << std::endl;
    print_line(fout, 60, '-');
    for (int i = 0; i < size; i++)
    {
        fout << std::setw(width) << c[i].type;
        print_text(fout, c[i].description, width);
        fout << std::endl;
    }
    fout.close();
}

void to_lower(char* string)
{
    for (int i = 0; i < std::strlen(string + 1); i++)
    {
        if (string[i] >= 'A' && string[i] <= 'Z') string[i] += 32;
    }
}

void camel_case(char* string)
{
    to_lower(string);
    bool flag= true;
    for (int i = 0; i < std::strlen(string) + 1; i++)
    {
        if (flag)
        {
            string[i] -= 32;
            flag = false;
        }
        if (string[i] == ' ') flag = true;
    }
}

char* create_name(char* name, char* p_surname , char* m_surname)
{
    char buffer[TEXT_LENGTH];
    char* fullname ;
    camel_case(name);
    camel_case(p_surname);
    camel_case(m_surname);
    std::strcpy(buffer, name);
    //std::
}

void read_data_customers_file(const char* file_path,
                              Customer*& c,
                              int& count,
                              CustomerType* t,
                              int size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    char m_surname[TEXT_LENGTH], p_surname[TEXT_LENGTH], name[TEXT_LENGTH];
    char full_name[TEXT_LENGTH];
    int dni;
    char x;
    while (true)
    {
        // 30594557,NICOLAS,ZUNIGA,RIVERO,E
        dni = read_int(fin, true);
        if (fin.eof()) break;
        read_static_string(fin, name, ',');
        read_static_string(fin, p_surname, ',');
        read_static_string(fin, m_surname , ',');
        x = read_char(fin, true);

    }
    fin.close();
}
