#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape 
{
public:
	explicit Circle(float radius);
	float Area() const override;
	void SetRadius(float radius);
	float GetRadius() const;

private:
	float m_radius;
};

#endif 

