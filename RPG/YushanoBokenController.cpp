#include "YushanoBokenController.h"
#include <iostream>

YushanoBokenController::YushanoBokenController()
    : turn(0), enemy(nullptr), hero(nullptr), boss(nullptr), level(1) {
    std::srand(std::time(nullptr));
}

int YushanoBokenController::startGame(Hero* hero) {
    this->hero = hero;
    generateEnemiesOrBoss();
    presentEnemyOrBoss();
    bosses.clear();
    return turn = 0;
}

int YushanoBokenController::HeroTurn(Option option) {
    if (hero->IsDisabled()) {
        return turn = 1;
    }

    if (option == Option::Attack) {
        if (enemy != nullptr) {
            enemy->ReceiveDamage(hero->GetAttack());
            if (enemy->IsDead()) {
                defeatEnemy(enemy);
                return turn = 0;
            }
        }
        else if (boss != nullptr) {
            boss->ReceiveDamage(hero->GetAttack());
            if (boss->IsDead()) {
                defeatBoss(boss);
                return turn = 0;
            }
        }
    }
    else if (option == Option::Use_Item) {
        useItem();
    }
    else if (option == Option::Magic) {
        useMagic();
    }
    return turn = 1;
}

void YushanoBokenController::defeatEnemy(Enemy* enemy) {
    std::cout << "+++" << enemy->GetName() << " is DEAD +++\n";
    Item* item2 = enemy->DropLoot();
    hero->AddItem(item2);
    std::cout << "===You receive " << item2->ToString() << "===\n";
    hero->LevelUp(enemy->GetExp());
    std::cout << "===You got " << enemy->GetExp() << " exp===\n";
    this->enemy = nullptr;
    generateEnemiesOrBoss();
    presentEnemyOrBoss();
}

void YushanoBokenController::defeatBoss(Boss* boss) {
    Item* item = boss->DropLoot();
    hero->AddItem(item);
    std::cout << "=====You receive " << item->ToString() << "=====\n";
    hero->LevelUp(boss->GetExp());
    std::cout << "=====You got " << boss->GetExp() << " exp =====\n";
    std::cout << "CONGRATULATIONS\nYou have defeated " << boss->GetName() << "\n";
    this->boss = nullptr;
    generateEnemiesOrBoss();
    presentEnemyOrBoss();
}

void YushanoBokenController::useItem() {
    bool isInventoryEmpty = hero->DisplayInventory();
    if (!isInventoryEmpty) {
        std::cout << "Choose an item #\n";
        int option;
        std::cin >> option;
        Item* item = chosenOption(option);
        hero->UseItem(item);
    }
    else {
        std::cout << "You don't have items in your inventory\n";
    }
}

void YushanoBokenController::useMagic() {
    bool isMagicEmpty = hero->DisplayMagics();
    if (isMagicEmpty) {
        std::cout << "You have no magic available.\n";
        return;
    }

    std::cout << "Select a magic: ";
    int option;
    std::cin >> option;
    option--; // Convert to 0-based index

    if (option >= 0 && option < hero->GetMagicCount()) {
        Magic* magic = hero->GetMagics(option);
        if (hero->GetMp() >= magic->GetMpCost()) {
            hero->SetMp(hero->GetMp() - magic->GetMpCost());
            std::cout << hero->GetName() << " use " << magic->GetTypeString() << "\n";

            if (magic->GetType() == MagicType::CURE || magic->GetType() == MagicType::AERO) {
                hero->SetEffect(magic->GetEffectType());
            }
            else {
                if (enemy != nullptr) {
                    enemy->ReceiveDamage(magic->GetEffect());
                    enemy->SetEffect(magic->GetEffectType());
                    if (enemy->IsDead()) {
                        defeatEnemy(enemy);
                    }
                }
                else if (boss != nullptr) {
                    boss->ReceiveDamage(magic->GetEffect());
                    boss->SetEffect(magic->GetEffectType());
                    if (boss->IsDead()) {
                        defeatBoss(boss);
                    }
                }
            }
        }
        else {
            std::cout << "You don't have enough MP.\n";
        }
    }
    else {
        std::cout << "Invalid option.\n";
    }
}

int YushanoBokenController::EnemiesTurn() {
    if (enemy != nullptr) {
        enemy->ApplyStatusEffect();
        if (enemy->IsDisable()) {
            updateEnemyAndBossHealth();
            return 0;
        }

        updateEnemyAndBossHealth();
        if (enemy->IsDead()) {
            defeatEnemy(enemy);
            return 0;
        }

        hero->ReceiveDamage(enemy->GetAttack());
        std::cout << "++++YOU HAVE RECEIVED " << hero->GetDamageAfterDefense() << " DAMAGE+++++\n";
        return turn = 0;
    }
    else if (boss != nullptr) {
        boss->ApplyStatusEffect();
        if (boss->isDisable()) {
            updateEnemyAndBossHealth();
            return 0;
        }

        updateEnemyAndBossHealth();
        if (boss->IsDead()) {
            defeatBoss(boss);
            return 0;
        }

        int useSpecialAbility = std::rand() % 3 + 1;
        if (useSpecialAbility == 3) {
            boss->UseSpecialAbility(hero);
            std::cout << "++++++" << boss->GetName() << " USE " << boss->getAbility() << " SPECIAL+++++\n";
        }
        else {
            hero->ReceiveDamage(boss->GetAttack());
            std::cout << "+++++YOU HAVE RECEIVED " << hero->GetDamageAfterDefense() << " DAMAGE++++++\n";
        }
    }
    return turn = 0;
}

void YushanoBokenController::generateEnemiesOrBoss() {
    if (enemy == nullptr && boss == nullptr) {
        int generateEnemiesOrBoss = std::rand() % 5 + 1;
        if (hero->GetLevel() >= 10 && generateEnemiesOrBoss >= 4) {
            generateBossBasedOnLevel();
        }
        else {
            generateRandomEnemy();
        }
    }
}

void YushanoBokenController::generateBossBasedOnLevel() {
    int heroLevel = hero->GetLevel();
    if (heroLevel >= 10 && heroLevel <= 20) {
        generateBoss(BossName::SOLARIAS_IGNIS);
    }
    else if (heroLevel >= 21 && heroLevel <= 30) {
        generateBoss(BossName::VACORIUS_NEXIS);
    }
    else if (heroLevel >= 31 && heroLevel <= 40) {
        generateBoss(BossName::SOLARIAS_ULTIMA);
    }
    else if (heroLevel >= 50 && heroLevel <= 100) {
        generateBoss(BossName::SHIN_GODZILLA);
    }
}

void YushanoBokenController::generateBoss(BossName bossName) {
    if (std::find(bosses.begin(), bosses.end(), bossName) != bosses.end()) {
        generateRandomEnemy();
    }
    else {
        boss = new Boss(bossName);
        bosses.push_back(bossName);
        AddMessage("A terrifying boss has appeared: " + boss->GetName() + "!");
    }
}

void YushanoBokenController::generateRandomEnemy() {
    EnemyType enemyTypes[] = { /* Your enemy types here */ };
    int randomIndex = std::rand() % (sizeof(enemyTypes) / sizeof(enemyTypes[0]));
    enemy = new Enemy(enemyTypes[randomIndex]);

    if (hero->GetLevel() >= 6) {
        enemy->LevelUp(level);
        level++;
    }

    AddMessage("An enemy appears: " + enemy->GetName() + "!");
}

Item* YushanoBokenController::chosenOption(int option) {
    try {
        if (option < 1 || option > hero->GetInventory().GetItems().size()) {
            throw std::out_of_range("Invalid option");
        }
        return hero->GetInventory().GetItems()[option - 1];
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Please enter a number between 1 and "
            << hero->GetInventory().GetItems().size() << std::endl;
        return nullptr;
    }
}

void YushanoBokenController::updateEnemyAndBossHealth() {
    std::string status;
    if (enemy != nullptr) {
        status = "ENEMY: " + enemy->GetName() +
            "\nHP: " + std::to_string(enemy->GetHp()) +
            "/" + std::to_string(enemy->GetMaxHp());
        if (!enemy->GetEffectDisplay().empty()) {
            status += "\nStatus: " + enemy->GetEffectDisplay();
        }
        AddMessage(status);
    }
    else if (boss != nullptr) {
        status = "BOSS: " + boss->GetName() +
            "\nHP: " + std::to_string(boss->GetHp()) +
            "/" + std::to_string(boss->GetMaxHp());
        if (!boss->GetEffectDisplay().empty()) {
            status += "\nStatus: " + boss->GetEffectDisplay();
        }
        AddMessage(status);
    }
}

void YushanoBokenController::presentEnemyOrBoss() {
    if (enemy != nullptr) {
        std::string info = "ENEMY ENCOUNTER!\n" +
            enemy->GetName() +
            "\nATK: " + std::to_string(enemy->GetAttack()) +
            "\nDEF: " + std::to_string(enemy->GetDefense());
        AddMessage(info);
    }
    else if (boss != nullptr) {
        std::string info = "BOSS BATTLE!\n" +
            boss->GetName() +
            "\nATK: " + std::to_string(boss->GetAttack()) +
            "\nDEF: " + std::to_string(boss->GetDefense()) +
            "\nSpecial: " + boss->GetAbility();
        AddMessage(info);
    }
}

void YushanoBokenController::AddMessage(const std::string& message) {
    messages.push_back(message);
    // Keep only the last 5 messages
    if (messages.size() > 5) {
        messages.erase(messages.begin());
    }
    messageTimer = 5.0f; // Display for 5 seconds
}

int YushanoBokenController::getLevel() const {
    return level;
}

void YushanoBokenController::setLevel(int level) {
    this->level = level;
}
