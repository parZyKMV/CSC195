#include "Circle.h"
#include <cmath>

Circle::Circle(float radius) : m_radius(radius) {}

float M_PI = 3.14;

float Circle::Area() const {
    return M_PI * m_radius * m_radius;
}

void Circle::SetRadius(float radius) {
    m_radius = radius;
}

float Circle::GetRadius() const {
    return m_radius;
}