#pragma once
#include "raylib.h"

class Ball {
private:
    Vector2 position;
    Vector2 velocity;
    float radius;

public:
    Ball(float x, float y, float r);
    void Update();
    void Draw();
    void Reset();
    Vector2 GetPosition() const;
    float GetRadius() const;
    Vector2 GetVelocity() const;
    void BounceX();
    void BounceY();
};
