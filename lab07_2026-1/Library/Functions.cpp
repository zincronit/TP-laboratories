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

Date read_date(std::ifstream& fin, bool read_character)
{
    Date d;
    char c;
    // 1/04/2023
    fin >> d.day >> c >> d.month >> c >> d.year;
    if (read_character) fin.ignore();
    d.format = d.year * 10000 + d.month * 100 + d.day;
    return d;
}

void print_date(std::ofstream& fout, Date d, int width)
{
    fout << std::right << std::setfill('0') << std::setw(2) << d.day << '/'
        << std::setw(2) << d.month << '/'
        << std::setw(4) << d.year << std::left << std::setfill(' ');
    print_spaces(fout, 10, width);
}

// int read_date(std::istream& fin, bool read_character)
// {
//     int dd, mm, yy;
//     char c;
//     fin >> dd;
//     if (fin.eof()) return -1;
//     fin >> c >> mm >> c >> yy;
//     if (read_character) fin.ignore();
//     return yy * 10000 + mm * 100 + dd;
// }
//
// void print_date(std::ofstream& fout, int date, int width)
// {
//     fout << std::right << std::setfill('0') << std::setw(2) << date % 100 << '/'
//         << std::setw(2) << date % 10000 / 100 << '/'
//         << std::setw(4) << date / 10000 << std::left << std::setfill(' ');
//     print_spaces(fout, 10, width);
// }

Time read_time(std::ifstream& fin, bool read_character)
{
    Time t;
    char c;
    fin >> t.hour >> c >> t.minute >> c >> t.second;
    if (read_character) fin.ignore();
    t.total_seconds = t.hour * 3600 + t.minute * 60 + t.second;
    return t;
}

void print_time(std::ofstream& fout, Time t, int width)
{
    t.hour = t.total_seconds / 3600;
    t.minute = t.total_seconds % 3600 / 60;
    t.second = t.total_seconds % 60;
    fout << std::right << std::setfill('0') << std::setw(2) << t.hour << ':'
        << std::setw(2) << t.minute << ':'
        << std::setw(2) << t.second << std::left << std::setfill(' ');
    print_spaces(fout, 8, width);
}

// int read_time(std::ifstream& fin, bool read_character)
// {
//     int hh, mm, ss;
//     char c;
//     fin >> hh >> c >> mm >> c >> ss;
//     if (read_character) fin.ignore();
//     return hh * 3600 + mm * 60 + ss;
// }
//
// void print_time(std::ofstream& fout, int time, int width)
// {
//     fout << std::right << std::setfill('0') << std::setw(2) << time / 3600 << ':'
//         << std::setw(2) << time % 3600 / 60 << ':'
//         << std::setw(2) << time % 60 << std::left << std::setfill(' ');
//     print_spaces(fout, 8, width);
// }

Code read_code(std::ifstream& fin, bool read_character)
{
    Code c;
    char x;
    fin >> c.value1 >> x >> c.value2 >> x >> c.value3;
    if (read_character) fin.ignore();
    c.code = c.value1 * 1000000 + c.value2 * 1000 + c.value3;
    return c;
}

void print_code(std::ofstream& fout, Code c, int width)
{
    fout << c.value1 << '-' << c.value2 << '-' << c.value3;
    print_spaces(fout, 11, width);
}

// int read_code(std::ifstream& fin, bool read_character)
// {
//     int code, code2, code3;
//     char c;
//     fin >> code >> c >> code2 >> c >> code3;
//     if (read_character) fin.ignore();
//     return code * 1000000 + code2 * 10000 + code3;
// }
//
// void print_code(std::ofstream& fout, int code, int width)
// {
//     fout << code / 1000000 << '-' << code / 10000 % 100 << '-' << code % 10000;
//     print_spaces(fout, 11, width);
// }

char* read_string(std::ifstream& fin, char delimiter)
{
    char buffer[TEXT_LENGTH];
    char* string = nullptr;
    fin.getline(buffer, TEXT_LENGTH, delimiter);
    if (fin.eof()) return string;
    string = new char[std::strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

int read_int(std::ifstream& fin, bool read_character)
{
    int value = 0;
    fin >> value;
    if (read_character) fin.ignore();
    return value;
}

double read_double(std::ifstream& fin, bool read_character)
{
    double value = 0;
    fin >> value;
    if (read_character) fin.ignore();
    return value;
}


void read_data_specialties_file(const char* file_path,
                                Doctor*& d,
                                int& count)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    d = new Doctor[MAX_DOCTORS];
    Doctor* doctors{};
    int doctors_count = 0;
    int specialty_code = 0;
    char c;
    while (true)
    {
        char* specialty_name = nullptr;
        // 576,PEDIATRIA,9846,AMEZQUITA EPIQUEN EVERT ROBERTO,418.176,
        specialty_code = read_int(fin, true);
        if (fin.eof()) break;
        specialty_name = read_string(fin, ',');
        while (true)
        {
            // 9846,AMEZQUITA EPIQUEN EVERT ROBERTO,418.176,
            d[count].code = read_int(fin, true);
            d[count].name = read_string(fin, ',');
            d[count].rate = read_double(fin, false);
            d[count].specialty.code = specialty_code;
            d[count].specialty.name = specialty_name;
            // std::cout << count <<  d[count].name << std::endl;
            count++;
            fin.get(c);
            if (c == '\n') break;
        }
    }
    fin.close();
}

void print_values_Doctors(const char* file_path,
                          Doctor* d,
                          int count)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    fout << "DOCTOR VALUES" << std::endl;
    print_line(fout, 150, '=');
    int width = 150 / 5;
    print_text(fout, "DOCTOR CODE", width);
    print_text(fout, "DOCTOR NAME", width);
    print_text(fout, "DOCTOR RATE", width);
    print_text(fout, "DOCTOR SPECIALTY", width);
    print_text(fout, "SPECIALTY CODE", width);
    fout << std::endl;
    print_line(fout, 150, '-');
    fout << std::fixed << std::setprecision(2);
    for (int i = 0; i < count; i++)
    {
        fout << std::setw(width - 10) << d[i].code;
        print_text(fout, d[i].name, width + 10);
        fout << std::setw(width) << d[i].rate;
        print_text(fout, d[i].specialty.name, width);
        fout << d[i].specialty.code << std::endl;
    }
    fout.close();
}

void swap_struct_doctor(Doctor& a, Doctor& b)
{
    Doctor temp;
    temp = a;
    a = b;
    b = temp;
}

void sort_doctors(Doctor* d, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (std::strcmp(d[i].name, d[j].name) > 0 or
                (std::strcmp(d[i].name, d[j].name) == 0 and d[i].rate < d[j].rate))
            {
                swap_struct_doctor(d[i], d[j]);
            }
        }
    }
}


void read_date_attentions_file(const char* file_path,
                               Attention*& a,
                               int& count)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    a = new Attention[MAX_ATTENTIONS];
    Date d;
    int trash;
    char c;
    Time admission_time, discharge_time;
    while (true)
    {
        // 1/04/2023,895,01:21:00,691-12-9990,03:13:54,4393,
        d = read_date(fin, true);
        if (fin.eof()) break;
        while (true)
        {
            trash = read_int(fin, true);
            admission_time = read_time(fin, true);
            a[count].patient_code = read_code(fin, true);
            discharge_time = read_time(fin, true);
            a[count].doctor_code = read_int(fin, false);
            a[count].duration.total_seconds = discharge_time.total_seconds - admission_time.total_seconds;
            if (admission_time.total_seconds > discharge_time.total_seconds)
            {
                a[count].duration.total_seconds = 24 * 3600 - admission_time.total_seconds + discharge_time.
                    total_seconds;
            }
            a[count].date = d;
            a[count].payment = a[count].duration.total_seconds / 3600.0;
            count++;
            fin.get(c);
            if (c == '\n' or fin.eof()) break;
        }
    }
    fin.close();
}

void print_array_attentions(const char* file_path,
                            Attention* a,
                            int count)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    fout << "ATTENTIONS VALUES" << std::endl;
    print_line(fout, 100, '=');
    int width = 100 / 5;
    print_text(fout, "DATE", width);
    print_text(fout, "PATIENT CODE", width);
    print_text(fout, "DURATION", width);
    print_text(fout, "DOCTOR CODE", width);
    fout << std::endl;
    print_line(fout, 100, '-');
    for (int i = 0; i < count; i++)
    {
        print_date(fout, a[i].date, width);
        print_code(fout, a[i].patient_code, width);
        print_time(fout, a[i].duration, width);
        fout << a[i].doctor_code << std::endl;
    }
    fout.close();
}

void to_lower_case(char* string)
{
    for (int i = 0; i < std::strlen(string); i++)
    {
        if (string[i] >= 'A' and string[i] <= 'Z') string[i] += 32;
    }
}

void camel_case(char* string)
{
    bool flag = true;
    to_lower_case(string);
    for (int i = 0; i < std::strlen(string); i++)
    {
        if (flag)
        {
            string[i] -= 32;
            flag = false;
        }
        if (string[i] == ' ' or string[i] == '_') flag = true;
    }
}

// void modify_name(const char* name, char* new_name)
// {
//     int count = 0;
//     int j = 0;
//     for (int i = 0; i < std::strlen(name); i++)
//     {
//         if (count == 0 or count == 2)
//         {
//             new_name[j] = name[i];
//             if (name[i] == ' ') new_name[j] = '_';
//             j++;
//         }
//         if (name[i] == ' ') count++;
//         if (count == 3)
//         {
//             new_name[j - 1] = '\0';
//             break;
//         }
//     }
//     camel_case(new_name);
// }

void modify_name(const char* fullname, char* new_name)
{
    char name[TEXT_LENGTH]{};
    char lastname[TEXT_LENGTH]{};
    char buffer[TEXT_LENGTH]{};
    int words = 0, j = 0;
    for (int i = 0; i < std::strlen(fullname) + 1; i++)
    {
        if (fullname[i] == ' ' or fullname[i] == '\0')
        {
            words++;
            if (words == 1)
            {
                buffer[j] = '\0';
                std::strcpy(lastname, buffer);
            }
            if (words == 3)
            {
                buffer[j] = '\0';
                std::strcpy(name, buffer);
                break;
            }
            j = 0;
        }
        else
        {
            buffer[j] = fullname[i];
            j++;
        }
    }
    camel_case(name);
    camel_case(lastname);
    std::strcpy(new_name, name);
    std::strcat(new_name, lastname);
}

char* generate_filename(const char* doctor, const char* specialty)
{
    char* filename = nullptr;

    char new_specialty[TEXT_LENGTH]{};
    char new_name[TEXT_LENGTH]{};
    modify_name(doctor, new_name);
    std::strcpy(new_specialty, specialty);
    camel_case(new_specialty);
    filename = new char[TEXT_LENGTH];
    std::strcpy(filename, "Reports/");
    std::strcat(filename, new_name);
    std::strcat(filename, "-");
    std::strcat(filename, new_specialty);
    std::strcat(filename, ".txt");
    return filename;
}


void print_static_part(std::ofstream& fout,
                       Doctor& d,
                       int width)
{
    fout << "DOCTOR: " << std::endl;
    fout << "CODE: " << d.code << std::endl;
    fout << "NAME: " << d.name << std::endl;
    fout << "RATE: " << d.rate << std::endl;
    print_line(fout, LINE_WIDTH, '-');
    fout << "SPECIALTY: " << std::endl;
    fout << "CODE: " << d.specialty.code << std::endl;
    fout << "NAME: " << d.specialty.name << std::endl;
    print_line(fout, LINE_WIDTH, '=');
    fout << "ATTENTIONS PROVIDED: " << std::endl;
    print_text(fout, "No. Date", width + 4);
    print_text(fout, "PATIENT CODE", width);
    print_text(fout, "DURATION", width);
    print_text(fout, "PAYMENT", width);
    fout << std::endl;
}

void print_dynamic_part(std::ofstream& fout,
                        Doctor& d,
                        Attention* a,
                        int count,
                        int width,
                        int& total_attentions,
                        double& total_payment,
                        Time& longest_duration)
{
    int j = 1;
    for (int i = 0; i < count; i++)
    {
        if (a[i].doctor_code == d.code)
        {
            fout << std::right << std::setfill('0') << std::setw(2) << j << ") ";
            print_date(fout, a[i].date, width);
            print_code(fout, a[i].patient_code, width);
            print_time(fout, a[i].duration, width);
            a[i].payment = d.rate * a[i].duration.total_seconds / 3600.0;
            fout << a[i].payment << std::endl;
            total_attentions++;
            total_payment += a[i].payment;
            if (longest_duration.total_seconds < a[i].duration.total_seconds)
            {
                longest_duration.total_seconds = a[i].duration.total_seconds;
            }
            j++;
        }
    }
}

void print_statistics(std::ofstream& fout,
                      int total_attentions,
                      double total_payment,
                      Time& longest_duration)
{
    print_line(fout, LINE_WIDTH, '=');
    fout << "TOTAL ATTENTIONS: " << total_attentions << std::endl;
    fout << "TOTAL PAYMENT: " << total_payment << std::endl;
    fout << "LONGEST ATTENTION DURATION: ";
    print_time(fout, longest_duration, 10);
    fout << std::endl;
}

void generate_report(const char* file_path,
                     Doctor& d,
                     Attention* a,
                     int attentions_count)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    int width = LINE_WIDTH / COLUMNS;
    int total_attentions = 0;
    Time longest_duration{};
    double total_payment = 0.0;
    fout << std::fixed << std::setprecision(2);
    print_static_part(fout, d, width);
    print_dynamic_part(fout, d, a, attentions_count, width, total_attentions,
                       total_payment, longest_duration);
    print_statistics(fout, total_attentions, total_payment, longest_duration);
    fout.close();
}


void print_reports(Doctor* d,
                   int doctors_count,
                   Attention* a,
                   int attentions_count)
{
    for (int i = 0; i < doctors_count; i++)
    {
        char* filename= nullptr;
        filename = generate_filename(d[i].name, d[i].specialty.name);
        generate_report(filename, d[i], a, attentions_count);
        delete[] filename;
    }
}
