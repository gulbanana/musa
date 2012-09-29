#pragma once
#include "IComponent.h"

class CShapeGeometry : public IComponent
{
public:
	static const ID ID = ID::ShapeGeometry;
	Polygon shape;
	Color4F color;
	float radius;

	CShapeGeometry(Polygon s, Color4F c, float r) : shape(s), color(c), radius(r) {}
};

