#pragma once

enum class BossName {
    SOLARIAS_IGNIS,
    VACORIUS_NEXIS,
    SOLARIAS_ULTIMA,
    SHIN_GODZILLA
};

enum class SpecialAbility {
    BURNING_PRIDE,
    CHAINS_OF_THE_VOID,
    UNSTOPPABLE_FORCE,
    ATOMIC_RAY
};

enum class EnemyType
{
    SLIME, GOBLIN, SKELETON
};

enum class ItemsType {
    POTION,
    ATTACK_STONE,
    DEFENSE_STONE,
    ETHER,

};

enum class StatusEffect {
    NONE,
    BURN,
    FREEZE,
    PARALYSIS,
    SHIELD,
    STOP,
    HEAL,
    RADIATION
    // Add new status effects here
};

enum class Option {
    Attack,
    Use_Item,
    Magic
};
