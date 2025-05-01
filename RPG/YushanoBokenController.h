#ifndef YUSHANO_BOKEN_CONTROLLER_H
#define YUSHANO_BOKEN_CONTROLLER_H

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Hero.h"
#include "Enemy.h"
#include "Boss.h"
#include "Enums.h"

class YushanoBokenController {
private:
    int turn;
    Enemy* enemy;
    Hero* hero;
    Boss* boss;
    int level;
    std::vector<BossName> bosses;

public:
    YushanoBokenController();
    int startGame(Hero* hero);
    int HeroTurn(Option option);
    int EnemiesTurn();
    int getLevel() const;
    void setLevel(int level);

private:
    void defeatEnemy(Enemy* enemy);
    void defeatBoss(Boss* boss);
    void useItem();
    void useMagic();
    void generateEnemiesOrBoss();
    void generateBossBasedOnLevel();
    void generateBoss(BossName bossName);
    void generateRandomEnemy();
    void updateEnemyAndBossHealth();
    void presentEnemyOrBoss();
    Item* chosenOption(int option);
};

#endif // YUSHANO_BOKEN_CONTROLLER_H