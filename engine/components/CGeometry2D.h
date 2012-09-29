#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"

class CGeometry2D : public IComponent
{
	IDENTIFIED(IComponent, Geometry2D);
public:
	std::vector<std::unique_ptr<IDrawable>> polys;
	Color4F color;

	CGeometry2D(Color4F c, std::unique_ptr<IDrawable> p) :  polys(), color(c)
	{
		polys.push_back(std::move(p));
	}

	Rect4F bounds();
};

