#pragma once
#include "Item.h"
#include "Enums.h"
#include <vector>
#include <string>
#include <raylib.h> // For sound and logging

class Inventory {
private:
    std::vector<Item> items;
    const int maxCapacity = 5;
    Sound addItemSound;
    Sound fullSound;

public:
    // Constructor/Destructor
    Inventory(const char* addSoundPath = "assets/sounds/inventory_add.wav",
        const char* fullSoundPath = "assets/sounds/inventory_full.wav");
    ~Inventory();

    // Core functionality
    bool AddItem(const Item& item);
    bool RemoveItem(ItemsType type);
    const Item* GetItem(ItemsType type) const;
    void Clear();

    // Utility
    bool IsFull() const { return items.size() >= maxCapacity; }
    int GetCount() const { return (int)items.size(); }
    bool IsEmpty() const { return items.empty(); }
    void Display() const;

    // Accessors
    const std::vector<Item>& GetItems() const { return items; }

    // Visual rendering
    void Draw(Vector2 position) const;
};

// Helper function
std::string ItemTypeToString(ItemType type);