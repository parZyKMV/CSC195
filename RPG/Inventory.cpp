#include "Inventory.h"
#include <algorithm>

Inventory::Inventory(const char* addSoundPath, const char* fullSoundPath) {
    // Load sounds
    if (FileExists(addSoundPath)) {
        addItemSound = LoadSound(addSoundPath);
    }
    else {
        TraceLog(LOG_WARNING, "Inventory add sound not found!");
        addItemSound = Sound{ 0 };
    }

    if (FileExists(fullSoundPath)) {
        fullSound = LoadSound(fullSoundPath);
    }
    else {
        TraceLog(LOG_WARNING, "Inventory full sound not found!");
        fullSound = Sound{ 0 };
    }
}

Inventory::~Inventory() {
    if (addItemSound.frameCount != 0) UnloadSound(addItemSound);
    if (fullSound.frameCount != 0) UnloadSound(fullSound);
}

bool Inventory::AddItem(const Item& item) {
    if (IsFull()) {
        TraceLog(LOG_WARNING, "Inventory is full (Capacity: %d/%d)", GetCount(), maxCapacity);
        if (fullSound.frameCount != 0) PlaySound(fullSound);
        return false;
    }

    items.push_back(item);
    TraceLog(LOG_INFO, "Added %s to inventory", ItemTypeToString(item.GetType()).c_str());

    if (addItemSound.frameCount != 0) {
        PlaySound(addItemSound);
    }
    return true;
}

bool Inventory::RemoveItem(ItemsType type) {
    auto it = std::find_if(items.begin(), items.end(),
        [type](const Item& i) { return i.GetType() == type; });

    if (it != items.end()) {
        items.erase(it);
        TraceLog(LOG_INFO, "Removed %s from inventory", ItemTypeToString(type).c_str());
        return true;
    }

    TraceLog(LOG_WARNING, "Item %s not found in inventory", ItemTypeToString(type).c_str());
    return false;
}

const Item* Inventory::GetItem(ItemsType type) const {
    auto it = std::find_if(items.begin(), items.end(),
        [type](const Item& i) { return i.GetType() == type; });
    return (it != items.end()) ? &(*it) : nullptr;
}

void Inventory::Clear() {
    items.clear();
    TraceLog(LOG_INFO, "Inventory cleared");
}

void Inventory::Display() const {
    if (IsEmpty()) {
        TraceLog(LOG_INFO, "Inventory is empty");
        return;
    }

    TraceLog(LOG_INFO, "Inventory (%d/%d):", GetCount(), maxCapacity);
    for (size_t i = 0; i < items.size(); i++) {
        TraceLog(LOG_INFO, "%zu. %s", i + 1, items[i].ToString().c_str());
    }
}

void Inventory::Draw(Vector2 position) const {
    // Background
    DrawRectangleRounded(
        Rectangle{ position.x, position.y, 250, 50 + 40 * (float)items.size() },
        0.1f, 9, Fade(BLACK, 0.7f)
    );

    // Title
    DrawText("INVENTORY", position.x + 10, position.y + 10, 20, WHITE);

    // Items
    for (size_t i = 0; i < items.size(); i++) {
        float yPos = position.y + 40 + (i * 35);

        // Item slot background
        DrawRectangleRounded(
            Rectangle{ position.x + 10, yPos, 230, 30 },
            0.2f, 5, Fade(DARKGRAY, 0.5f)
        );

        // Item info
        DrawText(
            TextFormat("%d. %s", i + 1, items[i].ToString().c_str()),
            position.x + 20,
            yPos + 5,
            18,
            WHITE
        );
    }

    // Capacity indicator
    DrawText(
        TextFormat("%d/%d", GetCount(), maxCapacity),
        position.x + 200,
        position.y + 15,
        18,
        IsFull() ? RED : GREEN
    );
}

std::string ItemTypeToString(ItemsType type) {
    switch (type) {
    case ItemsType::POTION: return "Health Potion";
    case ItemsType::ATTACK_STONE: return "Attack Stone";
    case ItemsType::DEFENSE_STONE: return "Defense Stone";
    case ItemsType::ETHER: return "Ether";
    default: return "Unknown Item";
    }
}