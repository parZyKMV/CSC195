#include "Item.h"
#include "Hero.h" 

Item::Item(ItemsType type) : type(type) {
    // Initialize item properties
    switch (type) {
    case ItemsType::POTION:
        effectValue = 10;
        description = "Restores 10 HP";
        break;
    case ItemsType::ATTACK_STONE:
        effectValue = 1;
        description = "+1 Attack permanently";
        break;
    case ItemsType::DEFENSE_STONE:
        effectValue = 2;
        description = "+2 Defense permanently";
        break;
    case ItemsType::ETHER:
        effectValue = 5;
        description = "Restores 5 MP";
        break;
    }
}

Item::~Item() {
    if (useSound.frameCount != 0) {
        UnloadSound(useSound);
    }
}

bool Item::UseItem(Hero& hero) {
    bool wasUsed = false;

    switch (type) {
    case ItemsType::POTION: {
        int maxHp = hero.GetMaxHp();
        int currentHp = hero.GetHp();

        if (currentHp >= maxHp) {
            TraceLog(LOG_WARNING, "HP already full!");
            wasUsed = false;
        }
        else {
            int newHp = std::min(maxHp, currentHp + effectValue);
            hero.setHp(newHp);
            TraceLog(LOG_INFO, "Healed %d HP!", effectValue);
            wasUsed = true;
        }
        break;
    }

    case ItemsType::ATTACK_STONE: {
        int currentAttack = hero.GetAttack();
        if (currentAttack >= 100) {
            TraceLog(LOG_WARNING, "Attack at maximum!");
            wasUsed = false;
        }
        else {
            hero.SetAttack(currentAttack + effectValue);
            TraceLog(LOG_INFO, "Attack increased by %d!", effectValue);
            wasUsed = true;
        }
        break;
    }

    case ItemsType::DEFENSE_STONE: {
        int currentDefense = hero.GetDefense();
        if (currentDefense >= 100) {
            TraceLog(LOG_WARNING, "Defense at maximum!");
            wasUsed = false;
        }
        else {
            hero.SetDefense(currentDefense + effectValue);
            TraceLog(LOG_INFO, "Defense increased by %d!", effectValue);
            wasUsed = true;
        }
        break;
    }

    case ItemsType::ETHER: {
        int maxMp = hero.GetMaxMp();
        int currentMp = hero.GetMp();

        if (currentMp >= maxMp) {
            TraceLog(LOG_WARNING, "MP already full!");
            wasUsed = false;
        }
        else {
            int newMp = std::min(maxMp, currentMp + effectValue);
            hero.SetMp(newMp);
            TraceLog(LOG_INFO, "Restored %d MP!", effectValue);
            wasUsed = true;
        }
        break;
    }
    }

    // Play sound if item was used successfully
    if (wasUsed && useSound.frameCount != 0) {
        PlaySound(useSound);
    }

    return wasUsed;
}

std::string Item::ToString() const {
    return description;
}
