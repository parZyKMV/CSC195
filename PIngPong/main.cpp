#include "raylib.h"
#include "Game.h"

enum GameState {
    TITLE,
    PLAYING
};

int main() {
    InitWindow(800, 600, "Ping Pong Game");
    SetTargetFPS(60);

    Game game;
    GameState currentState = TITLE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (currentState == TITLE) {
            DrawText("PING PONG", GetScreenWidth() / 2 - MeasureText("PING PONG", 60) / 2, 150, 60, WHITE);
            DrawText("Press SPACE to start", GetScreenWidth() / 2 - MeasureText("Press SPACE to start", 30) / 2, 250, 30, GRAY);
            DrawText("Player 1: W/S    Player 2: Up/Down", GetScreenWidth() / 2 - MeasureText("Player 1: W/S    Player 2: Up/Down", 20) / 2, 320, 20, GRAY);

            if (IsKeyPressed(KEY_SPACE)) {
                currentState = PLAYING;
            }
        }
        else if (currentState == PLAYING) {
            game.Update();
            game.Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
