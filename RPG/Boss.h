#pragma once
#include "Character.h"
#include "Item.h"
#include "Enums.h"
#include <memory>
#include <raylib.h>

class Hero; // Forward declaration

class Boss : public Character {
private:
    SpecialAbility ability;
    Sound abilitySound;
    Texture2D bossTexture;

public:
    Boss(BossName name, const char* texturePath = nullptr, const char* soundPath = nullptr);
    ~Boss();

    // Combat
    SpecialAbility GetAbility() const { return ability; }
    bool IsDead() const override;
    std::unique_ptr<Item> DropLoot();
    void UseSpecialAbility(Hero& hero);

    // Rendering
    void Draw(Vector2 position) const override;

private:
    void InitializeBossStats(BossName name);
};
