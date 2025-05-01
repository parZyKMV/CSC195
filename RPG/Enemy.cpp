#include "Enemy.h"

Enemy::Enemy(EnemyType type, const char* spritePath)
{
    LoadEnemyStats(type);
}

Enemy::~Enemy() {
    if (sprite.id != 0) UnloadTexture(sprite);
    if (deathSound.frameCount != 0) UnloadSound(deathSound);
}

void Enemy::LoadEnemyStats(EnemyType type) {
    SetLevel(1);
    switch (type) {
    case EnemyType::SLIME:
        SetName("Slime");
        SetHp(5);
        SetAttack(3);
        SetDefense(2);
        SetExp(5);
        break;
    case EnemyType::SKELETON:
        SetName("Skeleton");
        SetHp(10);
        SetAttack(5);
        SetDefense(4);
        SetExp(7);
        break;
    case EnemyType::GOBLIN:
        SetName("Goblin");
        SetHp(15);
        SetAttack(6);
        SetDefense(5);
        SetExp(9);
        break;
    }
}


std::unique_ptr<Item> Enemy::DropLoot() {
    if (!IsDead()) return nullptr;

    // Random item drop
    std::uniform_int_distribution<int> dist(0, 3);
    ItemsType droppedType = static_cast<ItemsType>(dist(rng));

    return std::make_unique<Item>(droppedType);
}

void Enemy::LevelUp(int levels) {
    SetLevel(GetLevel() + levels);
    SetHp(GetHp() + levels);
    SetAttack(GetAttack() + levels);
    SetDefense(GetDefense() + levels);
    SetExp(GetExp() + levels);
}

void Enemy::Draw(Vector2 position) const {
    if (sprite.id != 0) {
        // Draw with red tint if damaged
        Color tint = IsDead() ? GRAY : (GetHp() < GetMaxHp() / 2) ? RED : WHITE;
        DrawTextureV(sprite, position, tint);
    }
    else {
        // Fallback: Draw colored circle
        DrawCircleV(position, 20, IsDead() ? DARKGRAY : RED);
    }
}