#include "YushanoBokenController.h"
#include <iostream>

YushanoBokenController::YushanoBokenController()
    : turn(0), hero(nullptr), level(1), messageTimer(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

int YushanoBokenController::StartGame(Hero* hero) {
    this->hero = hero;
    GenerateEnemiesOrBoss();
    PresentEnemyOrBoss();
    bosses.clear();
    turn = 0;
    return turn;
}

int YushanoBokenController::HeroTurn(Option option) {
    if (hero->IsDisabled()) {
        turn = 1;
        return turn;
    }

    switch (option) {
    case Option::Attack:
        if (enemy) {
            enemy->ReceiveDamage(hero->GetAttack());
            if (enemy->IsDead()) {
                DefeatEnemy();
                turn = 0;
                return turn;
            }
        }
        else if (boss) {
            boss->ReceiveDamage(hero->GetAttack());
            if (boss->IsDead()) {
                DefeatBoss();
                turn = 0;
                return turn;
            }
        }
        break;

    case Option::Use_Item:
        UseItem();
        break;

    case Option::Magic:
        UseMagic();
        break;
    }

    turn = 1;
    return turn;
}

void YushanoBokenController::DefeatEnemy() {
    AddMessage("+++" + enemy->GetName() + " is DEAD +++");

    Item* item = enemy->DropLoot();
    if (item) {
        hero->AddItem(item);
        AddMessage("===You receive " + item->ToString() + "===");
    }

    hero->LevelUp(enemy->GetExp());
    AddMessage("===You got " + std::to_string(enemy->GetExp()) + " exp===");

    enemy.reset();
    GenerateEnemiesOrBoss();
    PresentEnemyOrBoss();
}

void YushanoBokenController::DefeatBoss() {
    Item* item = boss->DropLoot();
    if (item) {
        hero->AddItem(item);
        AddMessage("=====You receive " + item->ToString() + "=====");
    }

    hero->LevelUp(boss->GetExp());
    AddMessage("=====You got " + std::to_string(boss->GetExp()) + " exp=====");
    AddMessage("CONGRATULATIONS\nYou have defeated " + boss->GetName());

    boss.reset();
    GenerateEnemiesOrBoss();
    PresentEnemyOrBoss();
}

void YushanoBokenController::UseItem() {
    if (!hero->DisplayInventory()) {
        std::cout << "Choose an item #\n";
        int option;
        std::cin >> option;
        Item* item = ChosenOption(option);
        if (item) {
            hero->UseItem(item);
        }
    }
    else {
        std::cout << "You don't have items in your inventory\n";
    }
}

void YushanoBokenController::UseMagic() {
    if (hero->DisplayMagics()) {
        std::cout << "You have no magic available.\n";
        return;
    }

    std::cout << "Select a magic: ";
    int option;
    std::cin >> option;
    option--;

    if (option >= 0 && option < hero->GetMagicCount()) {
        Magic* magic = hero->GetMagics(option);
        if (hero->GetMp() >= magic->GetMpCost()) {
            hero->SetMp(hero->GetMp() - magic->GetMpCost());
            AddMessage(hero->GetName() + " uses " + magic->GetTypeString());

            if (magic->GetType() == MagicType::CURE || magic->GetType() == MagicType::AERO) {
                hero->SetEffect(magic->GetEffectType());
            }
            else {
                if (enemy) {
                    enemy->ReceiveDamage(magic->GetEffect());
                    enemy->SetEffect(magic->GetEffectType());
                    if (enemy->IsDead()) {
                        DefeatEnemy();
                    }
                }
                else if (boss) {
                    boss->ReceiveDamage(magic->GetEffect());
                    boss->SetEffect(magic->GetEffectType());
                    if (boss->IsDead()) {
                        DefeatBoss();
                    }
                }
            }
        }
        else {
            AddMessage("You don't have enough MP.");
        }
    }
    else {
        AddMessage("Invalid option.");
    }
}

int YushanoBokenController::EnemiesTurn() {
    if (enemy) {
        enemy->ApplyStatusEffect();
        if (!enemy->IsDisabled()) {
            UpdateEnemyAndBossHealth();
            if (!enemy->IsDead()) {
                hero->ReceiveDamage(enemy->GetAttack());
                AddMessage("++++YOU RECEIVED " +
                    std::to_string(hero->GetDamageAfterDefense()) +
                    " DAMAGE+++++");
            }
            else {
                DefeatEnemy();
            }
        }
    }
    else if (boss) {
        boss->ApplyStatusEffect();
        if (!boss->IsDisabled()) {
            UpdateEnemyAndBossHealth();
            if (!boss->IsDead()) {
                if ((std::rand() % 3 + 1) == 3) {
                    boss->UseSpecialAbility(hero);
                    AddMessage("++++++" + boss->GetName() + " USES " +
                        boss->GetAbility() + " SPECIAL+++++");
                }
                else {
                    hero->ReceiveDamage(boss->GetAttack());
                    AddMessage("+++++YOU RECEIVED " +
                        std::to_string(hero->GetDamageAfterDefense()) +
                        " DAMAGE++++++");
                }
            }
            else {
                DefeatBoss();
            }
        }
    }

    turn = 0;
    return turn;
}

void YushanoBokenController::GenerateEnemiesOrBoss() {
    if (!enemy && !boss) {
        if (hero->GetLevel() >= 10 && (std::rand() % 5 + 1) >= 4) {
            GenerateBossBasedOnLevel();
        }
        else {
            GenerateRandomEnemy();
        }
    }
}

void YushanoBokenController::GenerateBossBasedOnLevel() {
    int heroLevel = hero->GetLevel();
    if (heroLevel >= 10 && heroLevel <= 20) {
        GenerateBoss(BossName::SOLARIAS_IGNIS);
    }
    else if (heroLevel >= 21 && heroLevel <= 30) {
        GenerateBoss(BossName::VACORIUS_NEXIS);
    }
    else if (heroLevel >= 31 && heroLevel <= 40) {
        GenerateBoss(BossName::SOLARIAS_ULTIMA);
    }
    else if (heroLevel >= 50 && heroLevel <= 100) {
        GenerateBoss(BossName::SHIN_GODZILLA);
    }
}

void YushanoBokenController::GenerateBoss(BossName bossName) {
    if (std::find(bosses.begin(), bosses.end(), bossName) != bosses.end()) {
        GenerateRandomEnemy();
    }
    else {
        boss = std::make_unique<Boss>(bossName);
        bosses.push_back(bossName);
        AddMessage("A terrifying boss has appeared: " + boss->GetName() + "!");
    }
}

void YushanoBokenController::GenerateRandomEnemy() {
    const std::array<EnemyType, 3> enemyTypes = {
        EnemyType::GOBLIN,
        EnemyType::ORC,
        EnemyType::DRAGON
    };

    EnemyType type = enemyTypes[std::rand() % enemyTypes.size()];
    enemy = std::make_unique<Enemy>(type);

    if (hero->GetLevel() >= 6) {
        enemy->LevelUp(level);
        level++;
    }

    AddMessage("An enemy appears: " + enemy->GetName() + "!");
}

Item* YushanoBokenController::ChosenOption(int option) {
    try {
        auto& items = hero->GetInventory().GetItems();
        if (option < 1 || option > static_cast<int>(items.size())) {
            throw std::out_of_range("Invalid option");
        }
        return items[option - 1];
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Please enter a number between 1 and "
            << hero->GetInventory().GetItems().size() << std::endl;
        return nullptr;
    }
}

void YushanoBokenController::UpdateEnemyAndBossHealth() {
    std::string status;
    if (enemy) {
        status = "ENEMY: " + enemy->GetName() +
            "\nHP: " + std::to_string(enemy->GetHp()) +
            "/" + std::to_string(enemy->GetMaxHp());
        if (!enemy->GetEffectDisplay().empty()) {
            status += "\nStatus: " + enemy->GetEffectDisplay();
        }
    }
    else if (boss) {
        status = "BOSS: " + boss->GetName() +
            "\nHP: " + std::to_string(boss->GetHp()) +
            "/" + std::to_string(boss->GetMaxHp());
        if (!boss->GetEffectDisplay().empty()) {
            status += "\nStatus: " + boss->GetEffectDisplay();
        }
    }
    AddMessage(status);
}

void YushanoBokenController::PresentEnemyOrBoss() {
    std::string info;
    if (enemy) {
        info = "ENEMY ENCOUNTER!\n" +
            enemy->GetName() +
            "\nATK: " + std::to_string(enemy->GetAttack()) +
            "\nDEF: " + std::to_string(enemy->GetDefense());
    }
    else if (boss) {
        info = "BOSS BATTLE!\n" +
            boss->GetName() +
            "\nATK: " + std::to_string(boss->GetAttack()) +
            "\nDEF: " + std::to_string(boss->GetDefense()) +
            "\nSpecial: " + boss->GetAbility();
    }
    AddMessage(info);
}

void YushanoBokenController::AddMessage(const std::string& message) {
    messages.push_back(message);
    if (messages.size() > 5) {
        messages.erase(messages.begin());
    }
    messageTimer = 5.0f;
}

int YushanoBokenController::GetLevel() const {
    return level;
}

void YushanoBokenController::SetLevel(int level) {
    this->level = level;
}