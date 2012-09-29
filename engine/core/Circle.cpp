#include "Circle.h"

Circle::Circle(float r) : radius(r) {}


Rect4F Circle::bounds2D()
{
	return Rect4F(-radius, -radius, radius, radius);
}

void Circle::draw()
{
}
