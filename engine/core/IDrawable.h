#pragma once
#include "Rect4F.h"
#include "Box6F.h"

class IDrawable
{
public:
	virtual ~IDrawable() {}
	virtual void draw() = 0;
	virtual Rect4F bounds2D() = 0;
	//virtual Box6F bounds3D();
};