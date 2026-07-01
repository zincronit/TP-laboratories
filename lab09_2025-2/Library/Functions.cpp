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

void print_text(std::ofstream& fout, const char* text, int width)
{
    fout << std::left << std::setw(width) << text;
}

int read_time(std::ifstream& fin, bool read_character)
{
    int hh, mm, ss;
    char c;
    // 1:41:48
    fin >> hh >> c >> mm >> c >> ss;
    if (read_character) fin.get();
    return hh * 3600 + mm * 60 + ss;
}

void print_time(std::ofstream& fout, int time)
{
    fout << std::right << std::setfill('0') << std::setw(2) << time / 3600 << ':'
        << std::setw(2) << time % 3600 / 60 << ':'
        << std::setw(2) << time % 60 << std::setfill(' ') << std::left;
}

char* read_string(std::ifstream& fin, char character)
{
    char buffer[TEXT_LENGTH];
    char* string = nullptr;
    fin.getline(buffer, TEXT_LENGTH, character);
    if (fin.eof()) return string;
    string = new char[std::strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

char* assign_string(char* buffer)
{
    char* string;
    string = new char[std::strlen(buffer) + 1];
    std::strcpy(string, buffer);
    return string;
}

double read_double(std::ifstream& fin, bool read_character)
{
    double value;
    fin >> value;
    if (read_character) fin.get();
    return value;
}

void initialize_list(struct List& list)
{
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

//
// Category assign_category(Category& c)
// {
//     Category temp;
//     temp.code = assign_string(c.code);
//     temp.name = assign_string(c.name);
//     temp.description = assign_string(c.description);
//     return temp;
// }

void insert_front(struct List& list, Category& c)
{
    Node* new_node;
    new_node = new Node;
    new_node->category = c;
    // new_node->category = assign_category(c);
    new_node->next = nullptr;
    if (list.head == nullptr)
    {
        list.head = new_node;
        list.size++;
    }
    else
    {
        new_node->next = list.head;
        list.head = new_node;
    }
}

//
// void insert_back(struct List& list, Category& c)
// {
//     Node* new_node;
//     new_node = new Node;
//     new_node->category = c;
//     new_node->next = nullptr;
//     if (list.head == nullptr and list.tail == nullptr)
//     {
//         new_node->next = nullptr;
//         list.head = new_node;
//         list.tail = new_node;
//         list.size++;
//     }
//     else
//     {
//         list.tail = new_node;
//     }
// }

void insert_back(struct List& list, Category& c)
{
    // without pointer Node* tail;
    Node* new_node;
    new_node = new Node;
    new_node->category = c;
    new_node->next = nullptr;
    if (list.head == nullptr)
    {
        list.head = new_node;
        list.size++;
    }
    else
    {
        Node* temp = list.head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void insert_sorted(struct List& list, Category& c)
{
    Node* new_node;
    new_node = new Node;
    new_node->category = c;
    new_node->next = nullptr;
    Node* curr = list.head;
    Node* prev = nullptr;
    while (curr != nullptr)
    {
        if (std::strcmp(curr->category.name, c.name) > 0) break;
        prev = curr;
        curr = curr->next;
    }
    new_node->next = curr;
    list.size++;
    if (prev == nullptr) list.head = new_node;
    else prev->next = new_node;
}

void read_data_categories_file(const char* filepath,
                               List& list)
{
    std::ifstream fin;
    open_input_file(fin, filepath);
    initialize_list(list);
    char buffer[TEXT_LENGTH]{};
    while (true)
    {
        Category c{};
        fin.getline(buffer, TEXT_LENGTH, ',');
        if (fin.eof()) break;
        c.name = read_string(fin, ',');
        c.description = read_string(fin, '\n');
        c.code = assign_string(buffer);
        // insert_front(list, c);
        // insert_back(list, c);
        insert_sorted(list, c);
    }
    fin.close();
}

void print_data_categories(const char* filepath,
                           List& list)
{
    std::ofstream fout;
    open_output_file(fout, filepath);
    fout << "CATEGORIES" << std::endl;
    print_line(fout, 130, '=');
    int width = 130 / 3;
    print_text(fout, "CODE", width - 30);
    print_text(fout, "NAME", width);
    print_text(fout, "DESCRIPTION", width);
    fout << std::endl;
    print_line(fout, 130, '-');
    Node* temp = list.head;

    while (temp->next != nullptr)
    {
        Category& c = temp->category;
        print_text(fout, c.code, width - 30);
        print_text(fout, c.name, width);
        print_text(fout, c.description, width);
        fout << std::endl;
        temp = temp->next;
    }
    fout.close();
}

void print_title(std::ofstream& fout, const char* title)
{
    fout << std::right << std::setw((LINE_WIDTH + std::strlen(title)) / 2) << title << std::endl;
}

void print_information(std::ofstream& fout, struct List& list, bool first_part)
{
    Node* curr = list.head;
    while (curr != nullptr)
    {
        Category& c = curr->category;
        fout << std::left;
        fout << std::setw(15) << "Code: " << c.code << std::endl;
        fout << std::setw(15) << "Name: " << c.name << std::endl;
        fout << std::setw(15) << "Description: " << c.description << std::endl;
        print_line(fout, LINE_WIDTH, '-');
        if (first_part)
        {
            fout << "NONE" << std::endl;
        }
        else
        {
            fout << "INFORMACION DE LAS REPORDUCCIONES" << std::endl;
            fout << "DURACION MAXIMA" << std::endl;
            fout << "NOBMRE DE CANAL" << std::endl;
            fout << std::setw(14) << "NOMBRE DEL CANAL" << c.name << std::endl;
            fout << std::setw(14) << "DURACION" << c.max_duration << std::endl;
            print_line(fout, LINE_WIDTH, '-');
            fout << "LIST DE DROP-OFF ";
            for (int i = 0; i < c.reproductions_count; i++)
            {
                fout << c.arr_drop_off[i] << "   ";
            }
        }
        print_line(fout, LINE_WIDTH, '=');
        curr = curr->next;
    }
}

void print_report(const char* filepath, struct List& list, bool first_part)
{
    std::ofstream fout;
    open_output_file(fout, filepath);
    print_title(fout, "REPORT OF CATEGORIES");
    print_information(fout, list, first_part);

    fout.close();
}

Node* find_pointer(struct List& list, const char* code)
{
    Node* curr = list.head;
    while (curr != nullptr)
    {
        if (std::strcmp(curr->category.code, code) == 0) return curr;
        curr = curr->next;
    }
    return nullptr;
}

void read_data_reproductions_file(const char* filepath,
                                  struct List& list)
{
    std::ifstream fin;
    open_input_file(fin, filepath);
    int time = 0;
    char buffer[TEXT_LENGTH]{}, name[TEXT_LENGTH]{};
    while (true)
    {
        Category c{};
        // ZT132U54,Sardoche,4.41,1:41:48
        fin.getline(buffer, TEXT_LENGTH, ',');
        if (fin.eof()) break;
        Node* curr = find_pointer(list, buffer);
        if (curr == nullptr)
        {
            std::cout << "Not found code " << buffer << std::endl;
            fin.ignore(100, '\n');
            continue;
        }
        c.channel_max_duration = new char[TEXT_LENGTH]{};
        fin.getline(name, TEXT_LENGTH, ',');
        c.arr_drop_off[c.reproductions_count] = read_double(fin, true);
        c.reproductions_count++;
        time = read_time(fin, true);
        c.total_duration += time;
        if (time > c.max_duration)
        {
            std::strcpy(c.channel_max_duration, name);
            c.max_duration = time;
        }
        curr->category = c;
    }
    fin.close();
}

void calculate_avg_drop_off(struct List& list)
{
    Node* curr = list.head;
    while (curr != nullptr)
    {
        Category& c = curr->category;
        for (int i = 0; i < c.reproductions_count; i++) c.avg_drop_off += c.arr_drop_off[i];
        c.avg_drop_off /= double(c.reproductions_count);
        curr = curr->next;
    }
}
