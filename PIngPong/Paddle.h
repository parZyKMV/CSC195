#pragma once
#include "raylib.h"

class Paddle {
private:
    Rectangle rect;
    float speed;

public:
    Paddle(float x, float y, float width, float height);
    void Update(bool upKey, bool downKey);
    void Draw();
    Rectangle GetRect() const;
};
