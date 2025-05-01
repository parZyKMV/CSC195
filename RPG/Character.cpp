#include "Character.h"
#include <algorithm>
#include <cstdlib>

Character::Character(const std::string& name, int maxHp, int attack, int defense,
    const char* spritePath)
    : name(name), maxHp(maxHp), hp(maxHp), attack(attack), defense(defense),
    level(1), exp(0), isDisable(false), damageAfterDefense(0),
    effect(StatusEffect::NONE), durationOfEffect(0), position{ 0, 0 },
    framesCounter(0), currentFrame(0) {

    // Load sprite
    if (spritePath) {
        sprite = LoadTexture(spritePath);
        frameRec = { 0, 0, (float)sprite.width / 4, (float)sprite.height };
    }

    // Load sound
    
}

Character::~Character() {
    if (sprite.id != 0) UnloadTexture(sprite);
    if (hurtSound.frameCount != 0) UnloadSound(hurtSound);
}

int Character::CalculateDamage() const {
    int baseDamage = attack;

    // Status effect modifiers
    if (effect == StatusEffect::BURN && durationOfEffect <= 3) {
        baseDamage = (int)(baseDamage * 0.8f); // 20% reduction
    }

    return baseDamage;
}

void Character::ReceiveDamage(int damage) {
    if (damage <= 0) return;

    // Shield reduces damage by 50%
    if (effect == StatusEffect::SHIELD && durationOfEffect <= 5) {
        damage = (int)(damage * 0.5f);
    }

    damageAfterDefense = std::max(1, damage - (defense / 2));
    hp = std::max(0, hp - damageAfterDefense);

    if (hurtSound.frameCount != 0) {
        PlaySound(hurtSound);
    }
}

bool Character::IsDead() const {
    return hp <= 0;
}

void Character::SetEffect(StatusEffect newEffect) {
    effect = newEffect;
    durationOfEffect = 1;

    switch (effect) {
    case StatusEffect::BURN:
        effectDisplay = u8"🔥";
        TraceLog(LOG_INFO, "%s has been burned!", name.c_str());
        break;

    case StatusEffect::FREEZE:
        effectDisplay = u8"❄️";
        isDisable = true;
        TraceLog(LOG_INFO, "%s has been frozen!", name.c_str());
        break;

    case StatusEffect::PARALYSIS:
        effectDisplay = u8"⚡";
        TraceLog(LOG_INFO, "%s has been paralyzed!", name.c_str());
        break;

    case StatusEffect::SHIELD:
        effectDisplay = u8"🛡️";
        TraceLog(LOG_INFO, "%s activated a shield!", name.c_str());
        break;

    case StatusEffect::STOP:
        effectDisplay = u8"⏳";
        isDisable = true;
        TraceLog(LOG_INFO, "%s has been stopped!", name.c_str());
        break;

    case StatusEffect::HEAL:
        hp = std::min(maxHp, hp + 8);
        TraceLog(LOG_INFO, "%s healed 8 HP!", name.c_str());
        break;

    case StatusEffect::RADIATION:
        effectDisplay = u8"☢️";
        TraceLog(LOG_INFO, "%s has been irradiated!", name.c_str());
        break;

    default:
        break;
    }
}

void Character::ApplyStatusEffect() {
    if (effect == StatusEffect::NONE) return;

    switch (effect) {
    case StatusEffect::BURN:
        if (durationOfEffect <= 3) {
            hp = std::max(0, hp - 1);
            TraceLog(LOG_INFO, "%s takes 1 burn damage!", name.c_str());
        }
        else {
            effectDisplay.clear();
        }
        break;

    case StatusEffect::FREEZE:
        if (durationOfEffect <= 2) {
            isDisable = true;
        }
        else {
            isDisable = false;
            effectDisplay.clear();
            TraceLog(LOG_INFO, "%s thawed out!", name.c_str());
        }
        break;

    case StatusEffect::PARALYSIS:
        if (durationOfEffect <= 3) {
            if (rand() % 100 < 50) {
                isDisable = true;
                TraceLog(LOG_INFO, "%s is paralyzed!", name.c_str());
            }
        }
        else {
            effectDisplay.clear();
        }
        break;

    case StatusEffect::RADIATION:
        if (durationOfEffect <= 3) {
            hp = std::max(0, hp - 8);
            TraceLog(LOG_INFO, "%s takes 8 radiation damage!", name.c_str());
        }
        else {
            effectDisplay.clear();
        }
        break;

    case StatusEffect::SHIELD:
        if (durationOfEffect > 5) {
            effect = StatusEffect::NONE;
            effectDisplay.clear();
            TraceLog(LOG_INFO, "%s's shield expired!", name.c_str());
        }
        break;

    case StatusEffect::STOP:
        if (durationOfEffect > 3) {
            isDisable = false;
            effect = StatusEffect::NONE;
            effectDisplay.clear();
            TraceLog(LOG_INFO, "%s can move again!", name.c_str());
        }
        break;

    default:
        break;
    }

    durationOfEffect++;
}

void Character::BasicAttack(Character& target) {
    int damage = CalculateDamage();
    target.ReceiveDamage(damage);
    TraceLog(LOG_INFO, "%s attacks %s for %d damage!",
        name.c_str(), target.GetName().c_str(), damage);
}

void Character::UpdateAnimation() {
    framesCounter++;
    if (framesCounter >= 12) { // Adjust for animation speed
        framesCounter = 0;
        currentFrame++;

        if (currentFrame > 3) currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)sprite.width / 4;
    }
}

void Character::Draw() const {
    if (sprite.id != 0) {
        // Draw character sprite with current animation frame
        DrawTextureRec(sprite, frameRec, position, WHITE);

        // Draw status effect icon
        if (!effectDisplay.empty()) {
            DrawText(effectDisplay.c_str(),
                position.x + frameRec.width / 2 - 10,
                position.y - 30, 20, RED);
        }
    }
}

void Character::DrawHealthBar(Vector2 pos) const {
    float healthPercentage = (float)hp / (float)maxHp;
    Color healthColor = healthPercentage > 0.6f ? GREEN :
        healthPercentage > 0.3f ? YELLOW : RED;

    // Background
    DrawRectangle(pos.x, pos.y, 104, 14, GRAY);
    // Health bar
    DrawRectangle(pos.x + 2, pos.y + 2, (int)(100 * healthPercentage), 10, healthColor);
    // Text
    DrawText(TextFormat("%d/%d", hp, maxHp), pos.x + 30, pos.y + 2, 10, BLACK);
}
