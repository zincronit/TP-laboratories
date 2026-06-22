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

char* read_string(std::ifstream& fin, char delimiter)
{
    char buffer[TEXT_LENGTH];
    char* string = nullptr;
    fin.getline(buffer,TEXT_LENGTH, delimiter);
    if (fin.eof()) return string;
    string = new char[strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

Time read_time(std::ifstream& fin)
{
    Time t;
    char c;
    // 01:41:48
    fin >> t.hour >> c >> t.minute >> c >> t.second;
    t.total_seconds = t.hour * 3600 + t.minute * 60 + t.second;
    return t;
}

void print_time(std::ofstream& fout, Time t)
{
    fout << std::setfill('0') << std::right << std::setw(2) << t.hour << ':'
        << std::setw(2) << t.minute << ':' << std::setw(2) << t.second
        << std::setfill(' ') << std::left;
}

double read_double(std::ifstream& fin, bool read_delimiter)
{
    double d;
    fin >> d;
    if (read_delimiter) fin.get();
    return d;
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

void read_data_categories_file(const char* file_path,
                               Category*& categories,
                               int& size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    categories = new Category[MAX_CATEGORIES]{};
    // UM163F47,just chatting
    while (true)
    {
        char* category_code = nullptr;
        category_code = read_string(fin, ',');
        if (fin.eof()) break;
        categories[size].code = category_code;
        categories[size].name = read_string(fin, '\n');
        size++;
    }
    fin.close();
}

void print_categories_values(const char* file_path,
                             Category* categories,
                             int size)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    fout << "CATEGORIES VALUES" << std::endl;
    print_line(fout, 60, '=');
    int width = 60 / 2;
    print_text(fout, "CODE", width);
    print_text(fout, "NAME", width);
    fout << std::endl;
    print_line(fout, 60, '-');
    for (int i = 0; i < size; i++)
    {
        print_text(fout, categories[i].code, width - 10);
        print_text(fout, categories[i].name, width);
        fout << std::endl;
    }
    fout.close();
}

int find_index(Category* categories, char* category_code, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (std::strcmp(categories[i].code, category_code) == 0) return i;
    }
    return NOT_FOUND;
}

void read_data_reproductions_file(const char* file_path,
                                  Category* categories,
                                  int size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    char c;
    while (true)
    {
        // Sardoche,ZT132U54,4.410,01:41:48
        int index;
        char* channel_name = nullptr;
        char* category_code = nullptr;
        channel_name = read_string(fin, ',');
        if (fin.eof()) break;
        category_code = read_string(fin, ',');
        index = find_index(categories, category_code, size);
        if (index == NOT_FOUND)
        {
            std::cout << "CODE NOT FOUND: " << category_code << std::endl;
            fin.ignore(200, '\n');
            continue;
        }
        if (categories[index].reproductions == nullptr)
        {
            categories[index].reproductions = new Reproduction[MAX_REPRODUCTIONS];
        }
        int pos = categories[index].reproductions_count;
        categories[index].reproductions[pos].channel_name = channel_name;
        categories[index].reproductions[pos].rating = read_double(fin, true);
        // this functions doesn't get the character '\n' ;
        categories[index].reproductions[pos].duration = read_time(fin);
        categories[index].reproductions_count++;
        // std::cout << " contador "  << categories[index].reproductions_count << std::endl;
        fin.get(c);
        // if (c == '\n' or fin.eof()) break;
    }
    fin.close();
}

void update_categories_values(Category* c, int size)
{
    for ( int i=0 ; i< size; i++)
    {
        for (int j = 0 ; j< c[i].reproductions_count; j++)
        {
            c[i].total_duration.total_seconds += c[i].reproductions[j].duration.total_seconds;
            c[i].avg_rating += c[i].reproductions[j].rating;
        }
        c[i].avg_rating /= c[i].reproductions_count;
    }
}

void print_title(std::ofstream& fout, const char* title)
{
    fout << std::right << std::setw((LINE_WIDTH + std::strlen(title)) / 2) << title << std::endl;
}

void print_static_part(std::ofstream& fout,
                       Category* c,
                       int i,
                       int width)
{
    fout << "Category: " << c[i].code << std::endl;
    fout << "Name: " << c[i].name << std::endl;
    print_line(fout, LINE_WIDTH, '-');
    fout << "REPRODUCTIONS:" << std::endl;
    print_text(fout, "CHANNEL", width);
    print_text(fout, "RATING", width);
    print_text(fout, "DURATION", width);
    fout << std::endl;
}

void print_statistics(std::ofstream& fout, Category* c,int i)
{
    fout << "AVERAGE RATING:  " << c[i].avg_rating << std::endl;
    fout << "TOTAL DURATION:  " << c[i].total_duration.total_seconds << std::endl;
    print_line(fout, LINE_WIDTH, '=');

}
void print_dynamic_part(std::ofstream& fout,
                        Category* c,
                        int i,
                        int width)
{
    for (int j = 0; j < c[i].reproductions_count; j++)
    {
        print_text(fout, c[i].reproductions[j].channel_name, width);
        fout << std::setw(width) << c[i].reproductions[j].rating;
        print_time(fout, c[i].reproductions[j].duration);
        fout << std::endl;
    }
    print_line(fout, LINE_WIDTH, '-');
}

void print_report(const char* file_path,
                  Category* c,
                  int size)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    print_title(fout, "REPORT BY CATEGORIES");
    int width = LINE_WIDTH / COLUMNS;
    fout << std::fixed << std::setprecision(2);
    for (int i = 0; i < size; i++)
    {
        print_static_part(fout, c, i, width);
        print_dynamic_part(fout,
                           c,
                           i,
                           width);
        print_statistics(fout, c, i);
    }
    fout.close();
}
