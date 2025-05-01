#include "Magic.h"

Magic::Magic(MagicType type, const char* soundPath) : type(type) {
    // Initialize magic properties
    switch (type) {
    case MagicType::FIRE:
        mpCost = 5;
        effectValue = 3;
        statusEffectSymbol = u8"🔥";
        effectType = StatusEffect::BURN;
        break;

    case MagicType::BLIZZARD:
        mpCost = 3;
        effectValue = 2;
        statusEffectSymbol = u8"❄️";
        effectType = StatusEffect::FREEZE;
        break;

    case MagicType::THUNDER:
        mpCost = 7;
        effectValue = 6;
        statusEffectSymbol = u8"⚡";
        effectType = StatusEffect::PARALYSIS;
        break;

    case MagicType::AERO:
        mpCost = 10;
        effectValue = 4;
        statusEffectSymbol = u8"🌪️";
        effectType = StatusEffect::SHIELD;
        break;

    case MagicType::STOP:
        mpCost = 15;
        effectValue = 0;
        statusEffectSymbol = u8"⏳";
        effectType = StatusEffect::STOP;
        break;

    case MagicType::CURE:
        mpCost = 20;
        effectValue = 8;
        statusEffectSymbol = u8"💖";
        effectType = StatusEffect::HEAL;
        break;
    }

    // Load sound if provided
    if (soundPath) {
        castSound = LoadSound(soundPath);
    }
    else {
        castSound = Sound{ 0 }; // Null sound
    }
}

Magic::~Magic() {
    if (castSound.frameCount != 0) {
        UnloadSound(castSound);
    }
}

void Magic::PlayCastSound() const {
    if (castSound.frameCount != 0) {
        PlaySound(castSound);
    }
}

// Static factory methods
Magic Magic::CreateFire() {
    return Magic(MagicType::FIRE, "assets/sounds/fire.wav");
}

Magic Magic::CreateBlizzard() {
    return Magic(MagicType::BLIZZARD, "assets/sounds/blizzard.wav");
}

Magic Magic::CreateThunder() {
    return Magic(MagicType::THUNDER, "assets/sounds/thunder.wav");
}

Magic Magic::CreateAero() {
    return Magic(MagicType::AERO, "assets/sounds/wind.wav");
}

Magic Magic::CreateStop() {
    return Magic(MagicType::STOP, "assets/sounds/time.wav");
}

Magic Magic::CreateCure() {
    return Magic(MagicType::CURE, "assets/sounds/heal.wav");
}