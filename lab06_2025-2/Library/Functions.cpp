#include "Functions.hpp"

void open_output_file(std::ofstream& fout, const char* file_path)
{
    fout.open(file_path);
    if (not fout.is_open())
    {
        std::cout << "Error: could not open file " << file_path << std::endl;
        std::exit(1);
    }
}

void open_input_file(std::ifstream& fin, const char* file_path)
{
    fin.open(file_path);
    if (not fin.is_open())
    {
        std::cout << "Error: could not open file " << file_path << std::endl;
        std::exit(1);
    }
}

void print_spaces(std::ofstream& four, int extra, int width)
{
    for (int i = 0; i < width - extra; ++i) four.put(' ');
}

int read_date(std::ifstream& fin)
{
    int dd, mm, yy;
    char c;
    fin >> dd >> c >> mm >> c >> yy;
    return yy * 10000 + mm * 100 + dd;
}

void print_date(std::ofstream& fout, int time, int width)
{
    fout << std::right << std::setfill('0') << std::setw(2) << time % 100 << '/'
        << std::setw(2) << time % 10000 / 100 << '/'
        << std::setw(4) << time / 10000 << std::left << std::setfill(' ');
    print_spaces(fout, 10, width);
}

int read_time(std::ifstream& fin)
{
    int hh, mm, ss;
    char c;
    fin >> hh >> c >> mm >> c >> ss;
    return hh * 3600 + mm * 60 + ss;
}

void print_time(std::ofstream& fout, int time)
{
    fout << std::right << std::setfill('0') << std::setw(2) << time / 3600 << ':'
        << std::setw(2) << time % 3600 / 60 << ':'
        << std::setw(2) << time % 60 << std::left << std::setfill(' ');
}

void print_line(std::ofstream& fout, int width, char c)
{
    for (int i = 0; i < width; ++i) fout.put(c);
    fout << std::endl;
}

void print_text(std::ofstream& fout, const char* text, int width)
{
    fout << std::left << std::setw(width) << text;
}

char* change_format_name(const char* name)
{
    bool start_word = true;
    char* new_name = new char[strlen(name) + 1];
    std::strcpy(new_name, name);
    for (int i = 0; i < std::strlen(name); ++i)
    {
        if (start_word)
        {
            new_name[i] -= 32;
            start_word = false;
        }
        if (new_name[i] == '_' and new_name[i+1] > '9') start_word = true;
    }
    return new_name;
}

void generate_file_link(const char* stream_name, char* file_name, char* link)
{
    char* string = change_format_name(stream_name);
    std::strcat(file_name, "Reports/");
    std::strcat(file_name, string);
    std::strcat(file_name, ".txt");
    std::strcat(link, "https://Laboratory06_2025_2/Reports/");
    std::strcat(link, string);
    delete [] string;
}

char* read_string(std::ifstream& fin, char delimiter)
{
    char buffer[MAX_STRING_LENGTH];
    char* string;
    fin.getline(buffer, MAX_STRING_LENGTH, delimiter);
    string = new char[std::strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

void read_data_categories(const char* file_path,
                          char** stream_codes,
                          char** names,
                          int& size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);


    while (true)
    {
        // UM163F47   just_chatting
        stream_codes[size] = read_string(fin, ' ');
        if (fin.eof())
        {
            delete [] stream_codes[size];
            break;
        }
        fin >> std::ws;
        names[size] = read_string(fin, '\n');
        size++;
    }
    fin.close();
}

void report_arrays_categories(const char* file_path,
                              char** stream_codes,
                              char** names,
                              int size)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    fout << "Arrary categories file" << std::endl;
    print_line(fout, 60, '=');
    int width = 30;
    print_text(fout, "STREAM CODE", width);
    print_text(fout, "NAME", width);
    fout << std::endl;
    print_line(fout, 60, '-');
    for (int i = 0; i < size; ++i)
    {
        fout << std::setw(30) << stream_codes[i] << names[i] << std::endl;
    }
    fout.close();
}

void read_data_reproductions_file(const char* file_path,
                                  int* dates,
                                  char** channels,
                                  char** codes,
                                  double* rating,
                                  double* drop_off,
                                  int* stream_durations,
                                  int& size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    int date = 0;
    while (true)
    {
        // 31/8/2025  Sardoche    ZT132U54    4.410    0.715    1:41:48
        date = read_date(fin);
        if (fin.eof()) break;
        fin >> std::ws;
        channels[size] = read_string(fin, ' ');
        fin >> std::ws;
        codes[size] = read_string(fin, ' ');
        fin >> rating[size] >> drop_off[size];
        stream_durations[size] = read_time(fin);
        dates[size] = date;
        size++;
    }
    fin.close();
}

void print_arrays_reproductions(const char* file_path,
                                int* dates,
                                char** channels,
                                char** codes,
                                double* rating,
                                double* drop_off,
                                int* stream_durations,
                                int size)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    fout << "Arrary categories file" << std::endl;
    print_line(fout, 100, '=');
    int width = 100 / 6;
    print_text(fout, "DATE", width);
    print_text(fout, "STREAM CHANNEL", width);
    print_text(fout, "STREAM CATEGORY", width);
    print_text(fout, "RATING", width);
    print_text(fout, "DROP OFF", width);
    print_text(fout, "STREAM DURATION", width);
    fout << std::endl;
    print_line(fout, 100, '-');
    fout << std::fixed << std::setprecision(2);
    for (int i = 0; i < size; ++i)
    {
        print_date(fout, dates[i], width);
        fout << std::setw(width) << channels[i]
            << std::setw(width) << codes[i]
            << std::setw(width) << rating[i]
            << std::setw(width) << drop_off[i];
        print_time(fout, stream_durations[i]);
        fout << std::endl;
    }
    fout.close();
}

int find_index(char** arr, char* value, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (std::strcmp(arr[i], value) == 0) return i;
    }
    return NOT_FOUND;
}

void search_and_print_dynamic_part(std::ofstream& fout,
                                   char* stream_code,
                                   int* dates,
                                   char** channels,
                                   char** codes,
                                   double* rating,
                                   double* drop_off,
                                   int* stream_durations,
                                   int size,
                                   double& avg_rating,
                                   double& avg_drop_off,
                                   int& avg_duration,
                                   int& number)
{
    int width = LINE_WIDTH / COLUMNS;
    for (int i = 0; i < size; ++i)
    {
        if (std::strcmp(stream_code, codes[i]) == 0)
        {
            print_date(fout, dates[i], width);
            fout << std::setw(width) << channels[i]
                << std::setw(width) << rating[i]
                << std::setw(width) << drop_off[i];
            print_time(fout, stream_durations[i]);
            fout << std::endl;
            avg_rating += rating[i];
            avg_drop_off += drop_off[i];
            avg_duration += stream_durations[i];
            number++;
        }
    }
}

void print_avg(std::ofstream& fout,
               double avg_rating,
               double avg_drop_off,
               int avg_duration,
               int number)
{
    print_line(fout, LINE_WIDTH, '=');
    fout << "AVERAGE OF RATING  " << avg_rating/number << std::endl;
    fout << "AVERAGE DROP OFF  " << avg_drop_off/number << std::endl;
    fout << "TOTAL DURATION  " ;
    print_time(fout, avg_duration);
}

void print_report(const char* file_path,
                  const char* file_link,
                  char* stream_code,
                  char* name,
                  int* dates,
                  char** channels,
                  char** codes,
                  double* rating,
                  double* drop_off,
                  int* stream_durations,
                  int size)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    int width = LINE_WIDTH / COLUMNS;
    double avg_rating = 0.0, avg_drop_off = 0.0;
    int avg_duration = 0, number = 0;
    fout << "CODE: " << stream_code << std::endl;
    fout << "NAME: " << name << std::endl;
    fout << "LINK: " << file_link << std::endl;
    fout << "REPRODUCTIONS: " << std::endl;
    print_line(fout, LINE_WIDTH, '=');
    print_text(fout, "FECHA", width);
    print_text(fout, "STREAM CHANNEL", width);
    print_text(fout, "RATING", width);
    print_text(fout, "DROP OFF", width);
    print_text(fout, "STREAM DURATION", width);
    fout << std::endl;
    search_and_print_dynamic_part(fout,
                                  stream_code,
                                  dates,
                                  channels,
                                  codes,
                                  rating,
                                  drop_off,
                                  stream_durations,
                                  size,
                                  avg_rating,
                                  avg_drop_off,
                                  avg_duration,
                                  number);
    print_avg(fout, avg_rating, avg_drop_off, avg_duration, number);
    fout.close();
}

