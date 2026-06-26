//
// Created by zincronit on 6/14/26.
//


#include "Library/Functions.hpp"
#include "Library/Structs/Delivery.hpp"


int main()
{
    Driver* drivers = nullptr;
    int size_drivers = 0;

    read_data_rute_file("Data/rutas.csv",
                        drivers,
                        size_drivers);

    print_drivers_report("Reports/drivers_report.txt",
                         drivers,
                         size_drivers);


    sort_drivers(drivers, size_drivers);

    print_drivers_report("Reports/sorted_drivers_report.txt",
                         drivers,
                         size_drivers);

    Delivery* delivery = nullptr;
    int size_delivery = 0;

    read_data_deliveries_file("Data/envios.csv",
                              delivery,
                              size_delivery);

    sort_deliveries(delivery, size_delivery);

    print_report("Reports/report.txt",
                 drivers,
                 size_drivers,
                 delivery,
                 size_delivery);
    std::cout << size_delivery << std::endl << size_drivers;

    return 0;
}
