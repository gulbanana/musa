#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"

class CGeometry2D : public IComponent
{
public:
	static const ID ID = ID::Geometry2D;
	std::vector<std::unique_ptr<IDrawable>> polys;
	Color4F color;

	CGeometry2D(Color4F c, std::unique_ptr<IDrawable> p) :  polys(), color(c)
	{
		polys.push_back(std::move(p));
	}

	Rect4F bounds();
};

