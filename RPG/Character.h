#pragma once
#include <string>
#include <raylib.h>
#include <vector>

enum class StatusEffect {
    NONE, BURN, FREEZE, PARALYSIS, SHIELD, STOP, HEAL, RADIATION
};

class Character {
protected:
    std::string name;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int level;
    int exp;
    bool isDisable;
    int damageAfterDefense;
    StatusEffect effect;
    int durationOfEffect;
    std::string effectDisplay;
    Texture2D sprite;
    Sound hurtSound;

    // Animation variables
    Vector2 position;
    int framesCounter;
    int currentFrame;
    Rectangle frameRec;

public:
    Character() = default;
    Character(const std::string& name, int maxHp, int attack, int defense,
        const char* spritePath);
    virtual ~Character();

    // Core combat
    virtual int CalculateDamage() const;
    virtual void ReceiveDamage(int damage);
    virtual bool IsDead() const { return hp <= 0; }

    // Status effects
    void SetEffect(StatusEffect newEffect);
    void ApplyStatusEffect();
    void ClearEffects();

    // Combat actions
    virtual void BasicAttack(Character& target);
    void Defend();
    void UseItem(int itemId);

    // Animation
    void UpdateAnimation();
    virtual void Draw(Vector2 position) const = 0;
    void DrawHealthBar(Vector2 pos) const;

    // Getters & Setters
    virtual void SetName(const std::string& newName) { name = newName; }
    virtual void SetHp(int newHp) { hp = newHp; }
    virtual void SetAttack(int newAttack) { attack = newAttack; }
    virtual void SetDefense(int newDefense) { defense = newDefense; }
    virtual void SetLevel(int newLevel) { level = newLevel; }
    virtual void SetExp(int newExp) { exp = newExp; }

    // Getters
    const std::string& GetName() const { return name; }
    int GetHp() const { return hp; }
    int GetAttack() const { return attack; }
    int GetDefense() const { return defense; }
    int GetLevel() const { return level; }
    int GetExp() const { return exp; }
    int GetMaxHp() const { return maxHp; }
};