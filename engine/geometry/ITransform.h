#pragma once
#include "IRenderer.h"

class ITransform
{
public:
	virtual ~ITransform() {}
	virtual void accept(IRenderer* renderer) const = 0;
	virtual void eject(IRenderer* renderer) const = 0;
};
