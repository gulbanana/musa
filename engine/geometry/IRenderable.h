#pragma once
#include "IRenderer.h"

class IRenderable
{
public:
	virtual ~IRenderable() {}
	
	virtual void invite(IRenderer* renderer) const = 0;
	virtual void accept(IRenderer* renderer) const = 0;
};
