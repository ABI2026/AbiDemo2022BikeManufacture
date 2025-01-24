#include <iostream>
#include "Utils.h"
#include "Bike.h"

int main()
{
    Bike::Bike currBike = Bike::Bike("bike0Config.txt");

    std::cout << "Bike Complete? :" << currBike.complete() << "\n";
    std::cout << "Bike Weight: " << currBike.determineFullWeightKG() << "\n";
    std::cout << "Bike Price: " << currBike.determinePrice() << "\n";
    std::cout << "-----------------------------------------\n\n";
    currBike.displayComponents();

    return 0;
}
