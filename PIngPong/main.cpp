#include "raylib.h"
#include "Game.h"

int main() {
    InitWindow(800, 600, "Ping Pong Game");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        BeginDrawing();
        game.Update();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
