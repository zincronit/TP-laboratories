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

char* assign_string(const char* buffer)
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
    bool flag = true;
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

char* create_name(char* name, char* p_surname, char* m_surname)
{
    char buffer[TEXT_LENGTH];
    char* fullname;
    camel_case(name);
    camel_case(p_surname);
    camel_case(m_surname);
    std::strcat(buffer, p_surname);
    std::strcat(buffer, "/");
    std::strcpy(buffer, m_surname);
    std::strcat(buffer, "/");
    std::strcpy(buffer, name);
    fullname = new char[std::strlen(buffer) + 1];
    std::strcpy(fullname, buffer);
    return fullname;
}

int find_index_customer_type(CustomerType* t, int size, char letter)
{
    for (int i = 0; i < size; i++)
    {
        if (letter == t[i].type) return i;
    }
    return NOT_FOUND;
}

void read_data_customers_file(const char* file_path,
                              Customer*& c,
                              int& count,
                              CustomerType* t,
                              int size)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    c = new Customer[MAX_CUSTOMERS]{};
    char m_surname[TEXT_LENGTH], p_surname[TEXT_LENGTH], name[TEXT_LENGTH];
    int dni, index;
    char x;
    while (true)
    {
        // 30594557,NICOLAS,ZUNIGA,RIVERO,E
        dni = read_int(fin, true);
        if (fin.eof()) break;
        read_static_string(fin, name, ',');
        read_static_string(fin, p_surname, ',');
        read_static_string(fin, m_surname, ',');
        x = read_char(fin, true);
        c[count].dni = dni;
        c[count].name = create_name(name, p_surname, m_surname);
        index = find_index_customer_type(t, size, x);
        if (index != NOT_FOUND)
        {
            c[count].type.type = t[index].type;
            c[count].type.description = assign_string(t[index].description);
        }
        else
        {
            std::cout << "Type " << x << "not found " << std::endl;
        }
        count++;
    }
    fin.close();
}

void print_title(std::ofstream& fout, const char* title)
{
    print_line(fout, LINE_WIDTH, '=');
    fout << std::right << std::setw((LINE_WIDTH + std::strlen(title)) / 2) << title << std::endl;
}

void print_first_static_part(std::ofstream& fout, Customer& c, int number)
{
    int width = LINE_WIDTH / COLUMNS;
    print_line(fout, LINE_WIDTH, '=');
    print_text(fout, "      DNI", width);
    print_text(fout, "NOMBRE", width);
    print_text(fout, "TIPO DE CLIENTE", width);
    print_text(fout, "CANT. CUENTAS", width);
    fout << std::endl;
    fout << std::setw(width) << c.dni;
    print_text(fout, c.name, width);
    fout << c.type.type << "  - ";
    print_text(fout, c.type.description, width);
    if (number == 1) fout << '-' << std::endl;
    else fout << c.accounts_count << std::endl;
}

void print_second_static_part(std::ofstream& fout)
{
    int width = LINE_WIDTH / COLUMNS2;
    print_line(fout, LINE_WIDTH, '-');
    print_text(fout, "   CUENTA", width);
    print_text(fout, "SALDO INICIAL", width);
    print_text(fout, "ESTADO", width);
    print_text(fout, "CANT.DET", width);
    print_text(fout, "CANT.RET", width);
    print_text(fout, "CANT.TRAN", width);
    print_text(fout, "SALDO FINAL", width);
    fout << std::endl;
}

void print_customer_info(std::ofstream& fout, Customer& c, int number, int j)
{
    int width = LINE_WIDTH / COLUMNS2;
    if (number == 1 or number == 2)
    {
        if (number == 1)
        {
            print_text(fout, " -", width);
            print_text(fout, "-", width);
            print_text(fout, "-", width);
        }
        else
        {
            fout << std::setw(width) << c.account[j].account_no;
            fout << std::setw(width) << c.account[j].initial_balance;
            print_text(fout, c.account[j].status, width);
        }
        print_text(fout, "-", width);
        print_text(fout, "-", width);
        print_text(fout, "-", width);
        print_text(fout, "-", width);
        fout << std::endl;
    }
    else
    {
        fout << std::setw(width) << c.account[j].account_no;
        fout << std::setw(width) << c.account[j].initial_balance;
        print_text(fout, c.account[j].status, width);
        fout << std::setw(width) << c.account[j].deposit_count;
        fout << std::setw(width) << c.account[j].withdrawal_count;
        fout << std::setw(width) << c.account[j].transactions_count;
        fout << c.account[j].final_balance<< std::endl;
    }
    fout << "Transacciones" << std::endl;
    print_line(fout,LINE_WIDTH, '=');
}

void print_transactions(std::ofstream& fout, Transaction& t,int number)
{
    if (number == 1 or number == 2)
    {
        fout<< "NONE " << std::endl;
        return ;
    }
    fout << std::right << std::setw(7) << t.transaction_type;
    fout << std::setw(10) << t.amount;
    fout << std::endl;
}

void print_report(const char* file_path,
                  Customer* c,
                  int count,
                  int report_type)
{
    std::ofstream fout;
    open_output_file(fout, file_path);
    print_title(fout, "LISTADO DE CLIENTES");
    fout << std::fixed << std::setprecision(2);
    for (int i = 0; i < count; i++)
    {
        print_first_static_part(fout, c[i], report_type);
        for (int j = 0; j < c[i].accounts_count; j++)
        {
            print_second_static_part(fout);
            print_customer_info(fout, c[i], report_type, j);
            for (int k = 0; k < c[i].account[j].transactions_count; k++)
            {
                print_transactions(fout, c[i].account[j].transactions[k], report_type);
            }
        }
    }

    fout.close();
}

int find_index_customer(Customer* c, int count, int dni)
{
    for (int i = 0; i < count; i++)
    {
        if (c[i].dni == dni) return i;
    }
    return NOT_FOUND;
}

void read_data_accounts_file(const char* file_path,
                             Customer* c,
                             int count)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    int dni, index;
    while (true)
    {
        // 30594557,56916928,5683.23
        dni = read_int(fin, true);
        if (fin.eof()) break;
        index = find_index_customer(c, count, dni);
        if (index != NOT_FOUND)
        {
            if (c[index].account == nullptr) c[index].account = new Account[MAX_ACCOUNTS]{};
            Customer& customer = c[index];
            Account& a = customer.account[customer.accounts_count];
            a.account_no = read_int(fin, true);
            a.initial_balance = read_double(fin, true);
            a.status = assign_string((a.initial_balance >= 0) ? "HABILITADO" : "INHABILITADO");
            customer.accounts_count++;
        }
        else
        {
            std::cout << "DNI " << dni << " not found" << std::endl;
            fin.ignore(100 ,'\n');
        }
    }
    fin.close();
}

void find_index_account_no(Customer* c, int count, int number, int& x, int& y)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < c[i].accounts_count; j++)
        {
            if (c[i].account[j].account_no == number)
            {
                x = i;
                y = j;
                return;
            }
        }
    }
    x = NOT_FOUND;
    y = NOT_FOUND;
}

void read_data_transactions_file(const char* file_path,
                                 Customer* c,
                                 int count)
{
    std::ifstream fin;
    open_input_file(fin, file_path);
    int account_no;
    int x, y;
    char character;
    while (true)
    {
        // 66466160,D,13596.64,R,12536.72,R,11174.08
        account_no = read_int(fin, true);
        if (fin.eof()) break;
        find_index_account_no(c, count, account_no, x, y);
        if (x == NOT_FOUND and y == NOT_FOUND)
        {
            std::cout << "Not found account number " << account_no << std::endl;
            fin.ignore(300, '\n');
            continue;
        }
        while (true)
        {
            Customer& customer = c[x];
            Account& a = customer.account[y];
            if (a.transactions == nullptr) a.transactions = new Transaction[MAX_TRANSACTIONS]{};
            Transaction& t = a.transactions[a.transactions_count];
            t.transaction_type = read_char(fin, true);
            t.amount = read_double(fin, false);
            a.transactions_count++;
            if (t.transaction_type == 'D')
            {
                a.final_balance = a.initial_balance + t.amount;
                a.deposit_count++;
            }
            else
            {
                a.final_balance = a.initial_balance - t.amount;
                a.withdrawal_count++;
            }
            fin.get(character);
            if (character == '\n' or fin.eof()) break;
        }
    }
    fin.close();
}
