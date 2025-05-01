#pragma once
#include "Ball.h"
#include "Paddle.h"

class Game {
private:
    Ball ball;
    Paddle player1;
    Paddle player2;
    int score1;
    int score2;

public:
    Game();
    void Update();
    void Draw();
    void CheckCollisions();
};
