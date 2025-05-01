#pragma once
#include <string>
#include "raylib.h" // For sound effects
#include "Enums.h" // Your existing enum

enum class MagicType {
    FIRE,
    BLIZZARD,
    THUNDER,
    AERO,
    STOP,
    CURE
    // Add new magic types here
};

class Magic {
private:
    MagicType type;
    std::string statusEffectSymbol;
    int effectValue;
    StatusEffect effectType;
    int mpCost;
    Sound castSound;

public:
    Magic(MagicType type, const char* soundPath = nullptr);
    ~Magic();

    // Getters
    int GetEffect() const { return effectValue; }
    const std::string& GetStatusEffectSymbol() const { return statusEffectSymbol; }
    StatusEffect GetEffectType() const { return effectType; }
    MagicType GetType() const { return type; }
    int GetMpCost() const { return mpCost; }

    // Play the casting sound
    void PlayCastSound() const;

    // Static factory methods
    static Magic CreateFire();
    static Magic CreateBlizzard();
    static Magic CreateThunder();
    static Magic CreateAero();
    static Magic CreateStop();
    static Magic CreateCure();
};
