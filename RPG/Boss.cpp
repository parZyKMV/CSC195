#include "Boss.h"
#include "Hero.h"
#include <random>

Boss::Boss(BossName name, const char* texturePath, const char* soundPath) {
    // Load assets
    if (texturePath && FileExists(texturePath)) {
        bossTexture = LoadTexture(texturePath);
    }
    if (soundPath && FileExists(soundPath)) {
        abilitySound = LoadSound(soundPath);
    }

    InitializeBossStats(name);
}

Boss::~Boss() {
    if (bossTexture.id != 0) UnloadTexture(bossTexture);
    if (abilitySound.frameCount != 0) UnloadSound(abilitySound);
}

void Boss::InitializeBossStats(BossName name) {
    switch (name) {
    case BossName::SOLARIAS_IGNIS:
        SetName("Solarias Ignis");
        SetHp(40);
        SetAttack(20);
        SetDefense(20);
        SetExp(25);
        ability = SpecialAbility::BURNING_PRIDE;
        break;

    case BossName::VACORIUS_NEXIS:
        SetName("Vacorius Nexis");
        SetHp(60);
        SetAttack(25);
        SetDefense(25);
        SetExp(30);
        ability = SpecialAbility::CHAINS_OF_THE_VOID;
        break;

    case BossName::SOLARIAS_ULTIMA:
        SetName("Solaris Ultima");
        SetHp(60);
        SetAttack(30);
        SetDefense(30);
        SetExp(35);
        ability = SpecialAbility::UNSTOPPABLE_FORCE;
        break;

    case BossName::SHIN_GODZILLA:
        SetName("Shin Godzilla");
        SetHp(150);
        SetAttack(60);
        SetDefense(60);
        SetExp(100000);
        ability = SpecialAbility::ATOMIC_RAY;
        break;
    }
}

bool Boss::IsDead() const {
    return GetHp() <= 0;
}

std::unique_ptr<Item> Boss::DropLoot() {
    if (!IsDead()) return nullptr;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    ItemsType randomType = static_cast<ItemsType>(dist(gen));
    return std::make_unique<Item>(randomType);
}

void Boss::UseSpecialAbility(Hero& hero) {
    if (abilitySound.frameCount != 0) {
        PlaySound(abilitySound);
    }

    switch (ability) {
    case SpecialAbility::BURNING_PRIDE: {
        int boostedAttack = GetAttack() * 150 / 100;
        hero.SetEffect(StatusEffect::BURN);
        hero.ReceiveDamage(boostedAttack);
        break;
    }

    case SpecialAbility::CHAINS_OF_THE_VOID:
        hero.SetDisabled(true);
        break;

    case SpecialAbility::UNSTOPPABLE_FORCE:
        if (GetHp() <= 15) {
            SetAttack(GetAttack() + 6);
            SetDefense(GetDefense() + 6);
        }
        break;

    case SpecialAbility::ATOMIC_RAY:
        hero.ReceiveDamage(GetAttack() * 2);
        hero.SetEffect(StatusEffect::RADIATION);
        hero.SetDisabled(true);
        break;
    }
}

void Boss::Draw(Vector2 position) const {
    if (bossTexture.id != 0) {
        DrawTextureV(bossTexture, position, WHITE);
    }
    else {
        // Fallback drawing
        DrawCircleV(position, 30, RED);
        DrawText(GetName().c_str(), position.x - 50, position.y - 50, 20, WHITE);
    }
}