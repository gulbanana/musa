#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"

class CGeometry2D : public Identified<IComponent, CID::Geometry2D>
{
public:
	std::vector<std::unique_ptr<IDrawable>> polys;
	Color4F color;

	CGeometry2D(Color4F c, std::unique_ptr<IDrawable> p);
	Rect4F bounds();
};

