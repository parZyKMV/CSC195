#include "YushanoBokenUI.h"
#include <iostream>

YushanoBokenUI::YushanoBokenUI() : turn(0), hero(nullptr) {
    // Load textures
    galahadTexture = LoadTexture("resources/heroes/galahad.png");
    balinTexture = LoadTexture("resources/heroes/balin.png");
    elaineTexture = LoadTexture("resources/heroes/elaine.png");
}

YushanoBokenUI::~YushanoBokenUI() {
    UnloadTexture(galahadTexture);
    UnloadTexture(balinTexture);
    UnloadTexture(elaineTexture);
    if (hero) delete hero;
}

void YushanoBokenUI::Run() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Yushano Boken");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Update();
        Render();
    }

    CloseWindow();
}

void YushanoBokenUI::Update() {
    if (showGameOver) {
        if (IsKeyPressed(KEY_Y)) {
            // Reset game
            showGameOver = false;
            showHeroSelection = true;
            if (hero) delete hero;
            hero = nullptr;
        }
        else if (IsKeyPressed(KEY_N)) {
            CloseWindow();
        }
        return;
    }

    if (showHeroSelection) {
        if (IsKeyPressed(KEY_DOWN)) {
            selectedHeroIndex = (selectedHeroIndex + 1) % 3;
        }
        else if (IsKeyPressed(KEY_UP)) {
            selectedHeroIndex = (selectedHeroIndex - 1 + 3) % 3;
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            HeroName names[] = { HeroName::GALAHAD, HeroName::BALIN, HeroName::ELAINE };
            hero = new Hero(names[selectedHeroIndex]);
            turn = controller.startGame(hero);
            showHeroSelection = false;
            AddMessage("You chose " + hero->GetName());
        }
        return;
    }

    if (hero->IsDead()) {
        showGameOver = true;
        return;
    }

    ProcessInput();
}

void YushanoBokenUI::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (showHeroSelection) {
        // Draw hero selection screen
        DrawText("CHOOSE YOUR HERO", 400, 50, 40, GOLD);

        // Draw Galahad option
        Color galahadColor = selectedHeroIndex == 0 ? YELLOW : WHITE;
        DrawTexture(galahadTexture, 200, 150, WHITE);
        DrawText("1. Galahad", 220, 400, 30, galahadColor);
        DrawText("Health: 20", 220, 440, 20, galahadColor);
        DrawText("Attack: 6", 220, 470, 20, galahadColor);
        DrawText("Defense: 6", 220, 500, 20, galahadColor);

        // Draw Balin option
        Color balinColor = selectedHeroIndex == 1 ? YELLOW : WHITE;
        DrawTexture(balinTexture, 500, 150, WHITE);
        DrawText("2. Balin", 520, 400, 30, balinColor);
        DrawText("Health: 15", 520, 440, 20, balinColor);
        DrawText("Attack: 7", 520, 470, 20, balinColor);
        DrawText("Defense: 7", 520, 500, 20, balinColor);

        // Draw Elaine option
        Color elaineColor = selectedHeroIndex == 2 ? YELLOW : WHITE;
        DrawTexture(elaineTexture, 800, 150, WHITE);
        DrawText("3. Elaine", 820, 400, 30, elaineColor);
        DrawText("Health: 25", 820, 440, 20, elaineColor);
        DrawText("Attack: 5", 820, 470, 20, elaineColor);
        DrawText("Defense: 5", 820, 500, 20, elaineColor);

        DrawText("Use UP/DOWN arrows to select, ENTER to confirm", 350, 600, 20, GRAY);
    }
    else if (showGameOver) {
        DrawText("GAME OVER!", 500, 300, 50, RED);
        DrawText("Play again? (Y/N)", 520, 400, 30, WHITE);
    }
    else {
        // Draw game UI
        UpdateHeroStats();

        if (turn == 0) {
            ShowOptions();
        }

        // Draw messages
        for (size_t i = 0; i < messages.size(); i++) {
            DrawText(messages[i].c_str(), 50, 600 + (i * 30), 20, YELLOW);
        }
    }

    EndDrawing();
}

void YushanoBokenUI::ProcessInput() {
    if (turn == 0) {
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOptionIndex = (selectedOptionIndex + 1) % 3;
        }
        else if (IsKeyPressed(KEY_UP)) {
            selectedOptionIndex = (selectedOptionIndex - 1 + 3) % 3;
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            Option options[] = { Option::Attack, Option::Use_Item, Option::Magic };
            turn = controller.HeroTurn(options[selectedOptionIndex]);
            selectedOptionIndex = 0;
        }
    }
}

void YushanoBokenUI::ShowOptions() {
    DrawRectangle(50, 500, 300, 150, Color{ 0, 0, 0, 200 });
    DrawText("OPTIONS", 150, 510, 30, GOLD);

    Color attackColor = selectedOptionIndex == 0 ? YELLOW : WHITE;
    DrawText("1. Attack", 70, 550, 25, attackColor);

    Color itemColor = selectedOptionIndex == 1 ? YELLOW : WHITE;
    DrawText("2. Use Item", 70, 580, 25, itemColor);

    if (hero->GetLevel() >= 2) {
        Color magicColor = selectedOptionIndex == 2 ? YELLOW : WHITE;
        DrawText("3. Magic", 70, 610, 25, magicColor);
    }
}

void YushanoBokenUI::UpdateHeroStats() {
    DrawRectangle(900, 50, 350, 250, Color{ 0, 0, 0, 200 });
    DrawText("HERO STATUS", 950, 60, 30, GOLD);

    DrawText(("Name: " + hero->GetName()).c_str(), 920, 100, 20, WHITE);
    DrawText(("Level: " + std::to_string(hero->GetLevel())).c_str(), 920, 130, 20, WHITE);
    DrawText(("HP: " + std::to_string(hero->GetHp()) + "/" + std::to_string(hero->GetMaxHeroHp())).c_str(), 920, 160, 20, RED);
    DrawText(("MP: " + std::to_string(hero->GetMp())).c_str(), 920, 190, 20, BLUE);
    DrawText(("Attack: " + std::to_string(hero->GetAttack())).c_str(), 920, 220, 20, WHITE);
    DrawText(("Defense: " + std::to_string(hero->GetDefense())).c_str(), 920, 250, 20, WHITE);
}

void YushanoBokenUI::AddMessage(const std::string& message) {
    messages.push_back(message);
    if (messages.size() > 5) {
        messages.erase(messages.begin());
    }
}