#pragma once
#include "IRenderer.h"

class IRenderable
{
public:
	virtual ~IRenderable() = 0 {}
	virtual void accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) = 0;
};
