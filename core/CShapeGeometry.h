#pragma once
#include "types.h"
#include "IComponent.h"

class CShapeGeometry : public IComponent
{
public:
	static const CID ID = CID::ShapeGeometry;
	Polygon shape;
	Color4F color;
	float radius;

	CShapeGeometry(Polygon s, Color4F c, float r) : shape(s), color(c), radius(r) {}
};

