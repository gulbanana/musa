#pragma once
#include "IRenderer.h"

class IRenderable
{
public:
	virtual ~IRenderable() {}
	
	virtual void accept_enter(IRenderer* renderer) const = 0;
	virtual void accept_leave(IRenderer* renderer) const = 0;
};
