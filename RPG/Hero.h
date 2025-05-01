#pragma once
#include "Character.h"
#include "Inventory.h"
#include "Magic.h"
#include "Enums.h"
#include <vector>
#include <string>
#include <raylib.h> // For sound and input

enum class HeroName {
    GALAHAD,
    BALIN,
    ELAINE
};

class Hero : public Character {
private:
    int mp;
    int maxHp;
    int maxMp;
    bool isDisabled;
    Inventory inventory;
    std::vector<Magic> magics;
    int expToNextLevel;
    Sound levelUpSound;

    void LearnNewMagic();
    bool HasMagic(MagicType type) const;
    void ReplaceMagic(const Magic& newMagic);

public:
    Hero(HeroName name, const char* levelUpSoundPath = nullptr);
    ~Hero();

    // Level progression
    void GainExp(int exp);
    void LevelUp();

    // Inventory management
    void UseItem(ItemsType itemType);
    void AddItem(const Item& item);
    bool DisplayInventory() const;

    // Magic system
    bool DisplayMagics() const;
    bool CastMagic(int magicIndex, Character& target);

    // Getters
    int GetMp() const { return mp; }
    int GetMaxHp() const { return maxHp; }
    int GetMaxMp() const { return maxMp; }
    bool IsDisabled() const { return isDisabled; }
    const std::vector<Magic>& GetMagics() const { return magics; }
    int GetAttack() const { return attack; }
    int GetDefense() const { return defense; }

    // Manual clamp implementation
    template<typename T>
    constexpr const T& clamp(const T& value, const T& low, const T& high) {
        return (value < low) ? low : (high < value) ? high : value;
    }

    // Setters
    void SetMp(int value) { mp = clamp(value, 0, maxMp); }
    void SetMaxHp(int value) { maxHp = value; }
    void SetMaxMp(int value) { maxMp = value; }
    void SetDisabled(bool disabled) { isDisabled = disabled; }
    void setHp(int value) { hp = value; }
    void SetAttack(int value) { attack = value; }
    void SetDefense(int value) { defense = value; }
};