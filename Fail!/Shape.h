#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
public:
	virtual ~Shape() = default;
	virtual float Area() const = 0;

};

#endif

