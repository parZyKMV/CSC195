#include "TaqueriaDonTono.h"

TaqueriaDT::~TaqueriaDT() {
    for (Tacos* taco : tacos) {
        delete taco;
    }
}

void TaqueriaDT::AddTaco() {
    Tacos* newTaco = new Tacos();
    newTaco->Read(std::cout, std::cin);
    tacos.push_back(newTaco);
}

void TaqueriaDT::ShowEverthing() {
    if (tacos.empty()) {
        std::cout << "\nIs not tacos!\n";
        return;
    }

    std::cout << "\n--- TACOS MENU ---\n";
    for (Tacos* taco : tacos) {
        taco->Write(std::cout);
    }
}

void TaqueriaDT::LookForName(const std::string& name) {
    bool find = false;

    for (Tacos* taco : tacos) {
        if (taco->GetName() == name) {
            taco->Write(std::cout);
            find = true;
        }
    }

    if (!find) {
        std::cout << "\nNo Tacos with that name\n";
    }
}

void TaqueriaDT::LookForMeat(Tacos::tacosMeat meat) {
    bool find = false;

    std::cout << "\n--- TACOS OF " << Tacos::MeatToString(meat) << " ---\n";
    for (Tacos* taco : tacos) {
        if (taco->GetMeat() == meat) {
            taco->Write(std::cout);
            find = true;
        }
    }

    if (!find) {
        std::cout << "Is not tacos with that meat\n";
    }
}

void TaqueriaDT::LookForTortilla(Tacos::tortillaType tortilla) {
    bool find = false;

    std::cout << "\n--- TACOS WITH TORTILLA OF " << Tacos::TortillaToString(tortilla) << " ---\n";
    for (Tacos* taco : tacos) {
        if (taco->GetTortilla() == tortilla) {
            taco->Write(std::cout);
            find = true;
        }
    }

    if (!find) {
        std::cout << "Is not tacos with that tortilla\n";
    }
}