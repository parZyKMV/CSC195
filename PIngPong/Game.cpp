#include "Game.h"
#include "raylib.h"

Game::Game()
    : ball(400, 300, 10), player1(50, 250, 10, 100), player2(740, 250, 10, 100), score1(0), score2(0) {
}

void Game::Update() {
    ball.Update();
    player1.Update(IsKeyDown(KEY_W), IsKeyDown(KEY_S));
    player2.Update(IsKeyDown(KEY_UP), IsKeyDown(KEY_DOWN));
    CheckCollisions();
}

void Game::Draw() {
    ClearBackground(BLACK);
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), GRAY);
    ball.Draw();
    player1.Draw();
    player2.Draw();
    DrawText(TextFormat("%d", score1), 350, 20, 40, WHITE);
    DrawText(TextFormat("%d", score2), 420, 20, 40, WHITE);
}

void Game::CheckCollisions() {
    if (ball.GetPosition().y - ball.GetRadius() <= 0 ||
        ball.GetPosition().y + ball.GetRadius() >= GetScreenHeight()) {
        ball.BounceY();
    }

    if (CheckCollisionCircleRec(ball.GetPosition(), ball.GetRadius(), player1.GetRect()) ||
        CheckCollisionCircleRec(ball.GetPosition(), ball.GetRadius(), player2.GetRect())) {
        ball.BounceX();
    }

    if (ball.GetPosition().x < 0) {
        score2++;
        ball.Reset();
    }
    if (ball.GetPosition().x > GetScreenWidth()) {
        score1++;
        ball.Reset();
    }
}
