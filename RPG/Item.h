#pragma once
#include <string>
#include "Enums.h"
#include "raylib.h" // For sound effects

class Hero; // Forward declaration


class Item {
private:
    ItemsType type;
    std::string description;
    int effectValue;
    Sound useSound; // Sound when item is used

public:
    Item(ItemsType type);
    ~Item();

    ItemsType GetType() const { return type; }
    const std::string& GetDescription() const { return description; }

    bool UseItem(class Hero& hero); // Implemented after Hero class
    std::string ToString() const;

};