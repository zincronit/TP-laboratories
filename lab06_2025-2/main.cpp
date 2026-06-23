#include "Library/Functions.hpp"

int main()
{
    //Categories.txt
    char* stream_codes[MAX_CATEGORIES]{};
    char* names[MAX_CATEGORIES]{};
    int size_categories = 0;

    // Reproductions.txt
    int dates[MAX_REPRODUCTIONS]{};
    char* channels[MAX_REPRODUCTIONS]{};
    char* codes[MAX_REPRODUCTIONS]{};
    double rating[MAX_REPRODUCTIONS]{};
    double drop_off[MAX_REPRODUCTIONS]{};
    int stream_durations[MAX_REPRODUCTIONS]{};
    int size_reproductions = 0;

    read_data_categories("Data/Categories.txt",
                         stream_codes,
                         names,
                         size_categories);

    report_arrays_categories("Reports/test_report_categories.txt",
                             stream_codes,
                             names,
                             size_categories);

    read_data_reproductions_file("Data/Reproductions.txt",
                                 dates,
                                 channels,
                                 codes,
                                 rating,
                                 drop_off,
                                 stream_durations,
                                 size_reproductions);

    print_arrays_reproductions("Reports/test_report_reproductions.txt",
                               dates,
                               channels,
                               codes,
                               rating,
                               drop_off,
                               stream_durations,
                               size_reproductions);

    for (int i = 0; i < size_categories; i++)
    {
        char file_path[MAX_STRING_LENGTH]{};
        char file_link[MAX_STRING_LENGTH]{};
        generate_file_link(names[i], file_path, file_link);
        print_report(file_path,
                     file_link,
                     stream_codes[i],
                     names[i],
                     dates,
                     channels,
                     codes,
                     rating,
                     drop_off,
                     stream_durations,
                     size_reproductions);
    }

    return 0;
}
