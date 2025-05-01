#ifndef YUSHANO_BOKEN_UI_H
#define YUSHANO_BOKEN_UI_H

#include "raylib.h"
#include "YushanoBokenController.h"
#include <string>
#include <vector>

class YushanoBokenUI {
private:
    YushanoBokenController controller;
    int turn;
    Hero* hero;

    // UI State
    int selectedHeroIndex = 0;
    int selectedOptionIndex = 0;
    bool showingHeroSelection = true;
    bool gameOver = false;
    bool waitingForRestart = false;

    // Resources
    Font gameFont;
    Texture2D heroTextures[3]; // Textures for each hero

    // Messages
    std::vector<std::string> messages;
    float messageTimer = 0.0f;

public:
    YushanoBokenUI();
    ~YushanoBokenUI();

    void Initialize();
    void Run();
    void Update();
    void Render();

private:
    void ShowHeroes();
    HeroName ChooseHero();
    void ShowOptions();
    Option ChooseOption();
    void UpdateHeroStats();
    void AddMessage(const std::string& message);
    void DrawMessageLog();

    // Raylib-specific helpers
    void LoadResources();
    void UnloadResources();
    void DrawHeroSelection();
    void DrawGameUI();
    void DrawGameOverScreen();
};

#endif // YUSHANO_BOKEN_UI_H