#include "Base.h"

void Tacos::Read(std::ostream& ostream, std::istream& istream) {
    ostream << "Name of the Taco: ";
    std::getline(istream >> std::ws, name);

    ostream << "Type of meat (0-Asada, 1-Suadero, 2-Chorizo, 3-Bistec, 4-Barbacoa, 5-Carnitas, 6-Pastor, 7-Arrachera, 8-Cochinita Pibil, 9-Chiken): ";
    int meatInput;
    istream >> meatInput;
    meat = static_cast<tacosMeat>(meatInput);

    ostream << "Type of tortilla (0-Traditonial Corn, 1-Blue-Corn , 2-Other): ";
    int tortillaInput;
    istream >> tortillaInput;
    tortilla = static_cast<tortillaType>(tortillaInput);

    ostream << "Price: $";
    istream >> price;

    ostream << "With onions? (1-Yes, 0-No): ";
    istream >> withOnions;

    ostream << "With cilantro? (1-Yes, 0-No): ";
    istream >> withCilantro;
}

void Tacos::Write(std::ostream& ostream) {
    ostream << "\n--- " << name << " ---\n";
    ostream << "Meat: " << MeatToString(meat) << "\n";
    ostream << "Tortilla: " << TortillaToString(tortilla) << "\n";
    ostream << "Price: $" << price << "\n";
    ostream << "Onions: " << (withOnions ? "Yes" : "No") << "\n";
    ostream << "Cilantro: " << (withCilantro ? "Yes" : "No") << "\n";
}