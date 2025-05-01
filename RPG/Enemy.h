#pragma once
#include "Character.h"
#include "Item.h"
#include "Enums.h"
#include <raylib.h>
#include <random>

class Enemy : public Character {
private:
    Texture2D sprite;
    Sound deathSound;
    std::mt19937 rng; // Random number generator

public:
    Enemy(EnemyType type, const char* spritePath = nullptr);
    ~Enemy();

    std::unique_ptr<Item> DropLoot();
    void LevelUp(int levels);

    // Rendering
    void Draw(Vector2 position) const override;

private:
    void LoadEnemyStats(EnemyType type);
};