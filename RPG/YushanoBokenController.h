#ifndef YUSHANO_BOKEN_CONTROLLER_H
#define YUSHANO_BOKEN_CONTROLLER_H

#include "Hero.h"
#include "Enemy.h"
#include "Boss.h"
#include "Item.h"
#include "Inventory.h"
#include "Magic.h"
#include "Enums.h"

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class YushanoBokenController {
private:
    int turn;
    std::unique_ptr<Enemy> enemy;
    Hero* hero;
    std::unique_ptr<Boss> boss;
    int level;
    std::vector<BossName> bosses;
    std::vector<std::string> messages;
    float messageTimer;

public:
    YushanoBokenController();
    int StartGame(Hero* hero);
    int HeroTurn(Option option);
    int EnemiesTurn();
    int GetLevel() const;
    void SetLevel(int level);

private:
    void DefeatEnemy();
    void DefeatBoss();
    void UseItem();
    void UseMagic();
    void GenerateEnemiesOrBoss();
    void GenerateBossBasedOnLevel();
    void GenerateBoss(BossName bossName);
    void GenerateRandomEnemy();
    void UpdateEnemyAndBossHealth();
    void PresentEnemyOrBoss();
    Item* ChosenOption(int option);
    void AddMessage(const std::string& message);
};

#endif // YUSHANO_BOKEN_CONTROLLER_H