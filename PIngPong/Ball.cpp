#include "Ball.h"

Ball::Ball(float x, float y, float r)
    : position({ x, y }), radius(r), velocity({ 300.0f, 300.0f }) {
}

void Ball::Update() {
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
}

void Ball::Draw() {
    DrawCircleV(position, radius, WHITE);
}

void Ball::Reset() {
    position = { 400, 300 };
    velocity = { 300.0f, 300.0f };
}

Vector2 Ball::GetPosition() const {
    return position;
}

float Ball::GetRadius() const {
    return radius;
}

Vector2 Ball::GetVelocity() const {
    return velocity;
}

void Ball::BounceX() {
    velocity.x *= -1;
}

void Ball::BounceY() {
    velocity.y *= -1;
}
