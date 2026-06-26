#include "Functions.hpp"

void open_output_file(std::ofstream& fout, const char* file_path)
{
    fout.open(file_path);
    if (not fout.is_open())
    {
        std::cout << "Could not open file " << file_path << std::endl;
        std::exit(1);
    }
}

void open_input_file(std::ifstream& fin, const char* file_path)
{
    fin.open(file_path);
    if (not fin.is_open())
    {
        std::cout << "Could not open file " << file_path << std::endl;
        std::exit(1);
    }
}

void print_line(std::ofstream& fout, int width, char c)
{
    for (int i = 0; i < width; i++) fout.put(c);
    fout << std::endl;
}

void read_print_name(std::ofstream& fout, std::ifstream& fin)
{
    char c;
    fin >> std::ws;
    while (true)
    {
        fin.get(c);
        if (c == ' ' or c == '\n') break;
        if (c <= 'z' and c >= 'a') c -= 32;
        if (c == '_' or c == ')' or c == '(') c = ' ';
        if (c == '/' or c == '-' or c == '[' or c == ']') c = ' ';
        fout.put(c);
    }
}

void print_text(std::ofstream& fout, const char* text, int width)
{
    fout << std::left << std::setw(width) << text;
}

int read_time(std::ifstream& fin)
{
    int hh, mm;
    char c;
    fin >> hh >> c >> mm;
    return hh * 60 + mm;
}

void print_time(std::ofstream& fout, int time)
{
    fout << std::right << std::setfill('0') << std::setw(2) << time / 60 << ':'
        << std::setw(2) << time % 60 << std::left << std::setfill(' ');
}

void print_header(std::ofstream& fout)
{
    int width = LINE_WIDTH / COLUMNS;
    fout << std::endl;
    print_text(fout, "SCHEDULE", width + 2);
    print_text(fout, "STUDENTS", width + 3);
    print_text(fout, "PROFESSOR", width);
    fout << std::endl;
}

void find_print_data_professors(std::ofstream& fout,
                                std::ifstream& fin_professor,
                                int schedule,
                                int total_students,
                                int professor_code)
{
    fin_professor.clear();
    fin_professor.seekg(0, std::ios::beg);
    int code;
    int width = LINE_WIDTH / COLUMNS;
    while (true)
    {
        fin_professor >> code;
        if (fin_professor.eof()) break;
        if (code != professor_code)
        {
            fin_professor.ignore(90, '\n');
            continue;
        }
        fout << std::right << " " << std::setfill('0') << std::setw(4) << schedule
            << std::setfill(' ') << std::left << std::setw(width) << ' '
            << std::setw(width) << total_students;
        fout << professor_code << " - ";
        read_print_name(fout, fin_professor);
        fout << std::setw(10) << " - ";
        read_print_name(fout, fin_professor);
        fout << " - ";
        read_print_name(fout, fin_professor);
        fout << std::endl;
        if (code == professor_code) break;
    }
}


void print_header_dynamic_part(std::ofstream& fout)
{
    int width = LINE_WIDTH / COLUMNS;
    print_text(fout, "SESIONES", width);
    print_text(fout, "HORA", width-6);
    print_text(fout, "AULA", width);
    fout << std::endl;
}

void print_day(std::ofstream& fout, int day)
{
    switch (day)
    {
    case 1: fout << std::right << std::setw(10) << "Lunes" << std::left;
        break;
    case 2: fout << std::right << std::setw(10) << "Martes" << std::left;
        break;
    case 3: fout << std::right << std::setw(10) << "Miercoles" << std::left;
        break;
    case 4: fout << std::right << std::setw(10) << "Jueves" << std::left;
        break;
    case 5: fout << std::right << std::setw(10) << "Viernes" << std::left;
        break;
    case 6: fout << std::right << std::setw(10) << "Sabado" << std::left;
        break;
    case 7: fout << std::right << std::setw(10) << "Domingo" << std::left;
        break;
    }
}

void print_dynamic_part(std::ofstream& fout,
                        char code_char, int code_int,
                        int inic_time,
                        int end_time, int day, int& i)
{
    fout << i << ")";
    print_day(fout, day);
    fout << std::setw(13) << " ";
    print_time(fout, inic_time);
    fout << " - ";
    print_time(fout, end_time);
    fout << std::setw(15)<< " " << code_char << code_int << std::endl;
}

void read_dynamic_part(std::ofstream& fout,
                       std::ifstream& fin,
                       int& total_time)
{
    int day, inic_time, end_time, code_int, duration_time, i = 1;
    char code_char, c;
    while (true)
    {
        fin.get(c);
        if (c == '\n' or fin.eof()) break;
        fin >> day;
        inic_time = read_time(fin);
        end_time = read_time(fin);
        duration_time = end_time - inic_time;
        fin >> code_char >> code_int;
        print_dynamic_part(fout, code_char, code_int, inic_time, end_time, day, i);
        total_time += duration_time;
        i++;
    }
    fout << "Horas de dictado del horario: ";
    print_time(fout, total_time);
    fout << std::endl;
    print_line(fout, LINE_WIDTH, '-');

}

void read_join_data_sessions_file(std::ofstream& fout,
                                  std::ifstream& fin_professor,
                                  std::ifstream& fin_sessions,
                                  int course_code,
                                  int& total_time,
                                  int& students,
                                  int& curses_hours)
{
    int code, professor_code, total_students, schedule, total_time_curse=0;
    fin_sessions.clear();
    fin_sessions.seekg(0, std::ios::beg);
    while (true)
    {
        fin_sessions >> code;
        if (fin_sessions.eof()) break;
        if (code != course_code)
        {
            fin_sessions.ignore(150, '\n');
            continue;
        }
        fin_sessions >> schedule >> total_students >> professor_code;
        print_header(fout);
        find_print_data_professors(fout, fin_professor, schedule, total_students, professor_code);
        print_header_dynamic_part(fout);
        read_dynamic_part(fout, fin_sessions,total_time);
        total_time_curse += total_time;
        students += total_students;
    }
    curses_hours+= total_time_curse;
}


void read_join_data_courses_file(std::ofstream& fout,
                                 std::ifstream& fin_courses,
                                 std::ifstream& fin_professor,
                                 std::ifstream& fin_sessions)
{
    int course_code = 0,total_time_curse=0,students=0, curse_hours=0;
    double course_credit = 0.0;
    while (true)
    {
        fin_courses >> course_code;
        if (fin_courses.eof()) break;
        fin_courses >> course_credit;
        fout << "CURSOS: " << course_code << " - ";
        read_print_name(fout, fin_courses);
        fout << std::setw(20) << "CREDITOS: " << course_credit << " ESPECIALIDAD: ";
        read_print_name(fout, fin_courses);
        read_join_data_sessions_file(fout,
                                     fin_professor,
                                     fin_sessions,
                                     course_code,
                                     total_time_curse,
                                     students,
                                     curse_hours);
        print_line(fout , LINE_WIDTH, '-');
        fout <<"TOTAL DE HORAS DICTADAS EN EL CURSO   " ;
        print_time(fout, total_time_curse);
        fout << std::endl;
        fout << "TOTAL ALUMNOS MATRICULADOS     " << students;
        fout <<std::endl;
        print_line(fout, LINE_WIDTH, '=');
    }
}

void print_report(const char* output_path,
                  const char* courses_path,
                  const char* professor_path,
                  const char* sessions_path)
{
    std::ofstream fout;
    std::ifstream fin_courses, fin_professor, fin_sessions;
    open_output_file(fout, output_path);
    open_input_file(fin_courses, courses_path);
    open_input_file(fin_professor, professor_path);
    open_input_file(fin_sessions, sessions_path);
    fout << std::fixed << std::setprecision(2);
    fout << std::setw((LINE_WIDTH + 17) / 2) << "DETALLES DE CURSO" << std::endl;
    print_line(fout, LINE_WIDTH, '=');
    read_join_data_courses_file(fout,
                                fin_courses,
                                fin_professor,
                                fin_sessions);


    fout.close();
    fin_courses.close();
    fin_professor.close();
    fin_sessions.close();
}
