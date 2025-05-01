#include "Paddle.h"

Paddle::Paddle(float x, float y, float width, float height)
    : rect({ x, y, width, height }), speed(500.0f) {
}

void Paddle::Update(bool upKey, bool downKey) {
    if (upKey && rect.y > 0) rect.y -= speed * GetFrameTime();
    if (downKey && rect.y + rect.height < GetScreenHeight()) rect.y += speed * GetFrameTime();
}

void Paddle::Draw() {
    DrawRectangleRec(rect, WHITE);
}

Rectangle Paddle::GetRect() const {
    return rect;
}
