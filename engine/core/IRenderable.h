#pragma once
#include "IRenderer.h"

class IRenderable
{
public:
	virtual ~IRenderable() = 0 {}
	virtual void accept(IRenderer* renderer) = 0;
};