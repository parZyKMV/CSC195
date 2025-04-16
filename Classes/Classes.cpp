#include <iostream>
#include <limits>
#include "TaqueriaDonTono.h"

void MostrarMenuCarnes() {
    std::cout << "\nType of meat:\n";
    std::cout << "0 - Asada\n";
    std::cout << "1 - Suadero\n";
    std::cout << "2 - Chorizo\n";
    std::cout << "3 - Bistec\n";
    std::cout << "4 - Barbacoa\n";
    std::cout << "5 - Carnitas\n";
    std::cout << "6 - Al Pastor\n";
    std::cout << "7 - Arrachera\n";
    std::cout << "8 - Cochinita Pibil\n";
    std::cout << "9 - Chiken\n";
}

void MostrarMenuTortillas() {
    std::cout << "\nType of tortilla:\n";
    std::cout << "0 - Traditonial Corn\n";
    std::cout << "1 - Blue Corn\n";
}

int main() {
    TaqueriaDT taqueria;
    bool exit = false;

    while (!exit) {
        std::cout << "\n=== TAQUERIA DON TONO ===\n";
        std::cout << "1. Add Tacos\n";
        std::cout << "2. Show All the Tacos\n";
        std::cout << "3. Look by tacos name\n";
        std::cout << "4. Look tacos by meat type\n";
        std::cout << "5. Look tacos by tortilla type\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose a option: ";

        int options;
        std::cin >> options;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (options) {
        case 1:
            taqueria.AddTaco();
            break;
        case 2:
            taqueria.ShowEverthing();
            break;
        case 3: {
            std::cout << "Enter taco name: ";
            std::string name;
            std::getline(std::cin, name);
            taqueria.LookForName(name);
            break;
        }
        case 4: {
            MostrarMenuCarnes();
            std::cout << "Choose Meat: ";
            int meat;
            std::cin >> meat;
            taqueria.LookForMeat(static_cast<Tacos::tacosMeat>(meat));
            break;
        }
        case 5: {
            MostrarMenuTortillas();
            std::cout << "Choose Tortilla: ";
            int tortilla;
            std::cin >> tortilla;
            taqueria.LookForTortilla(static_cast<Tacos::tortillaType>(tortilla));
            break;
        }
        case 6:
            exit = true;
            std::cout << "\n¡Thanks for visiting the taqueria! Come back soon!\n";
            break;
        default:
            std::cout << "\nInvalid option. Please try again.\n";
        }
    }

    return 0;
}


