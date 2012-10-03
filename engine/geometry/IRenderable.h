#pragma once
#include "IRenderer.h"

class IRenderable
{
public:
	virtual ~IRenderable() {}
	virtual void accept(IRenderer* renderer, Color4F brush, Vec3<coord> position, Vec3<degrees> orientation) const = 0;
	virtual Box6<coord> bounds() const = 0;
};
