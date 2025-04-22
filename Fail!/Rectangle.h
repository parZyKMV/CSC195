#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(float h, float w);
	float Area() const override;
private:
	float m_height;
	float m_width;
};

#endif 

