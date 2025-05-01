#include "YushanoBokenUI.h"

int main() {
    // Initialize Raylib window and set target FPS
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Yushano Boken - C++ Version");
    SetTargetFPS(60);

    // Create and run the game UI
    YushanoBokenUI gameUI;
    gameUI.Run();

    // Clean up and exit
    CloseWindow();
    return 0;
}