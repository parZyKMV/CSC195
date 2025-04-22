#include "Rectangle.h"

Rectangle::Rectangle(float width, float height)
    : m_width(width), m_height(height) {
}

float Rectangle::Area() const {
    return m_width * m_height;
}