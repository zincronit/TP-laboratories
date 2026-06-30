#include "Functions.hpp"

void open_output_file(std::ofstream& fout, const char* filepath)
{
    fout.open(filepath);
    if (fout.is_open())
    {
        std::cout << "Error opening file " << filepath << std::endl;
        std::exit(1);
    }
}

void open_input_file(std::ifstream& fin, const char* filepath)
{
    fin.open(filepath);
    if (fin.is_open())
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
    Node* temp = list.head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = new_node;
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
        insert_front(list, c);
    }
    fin.close();
}
