#pragma once
#include "IRenderer.h"

class IMaterial
{
public:
	virtual ~IMaterial() {}
	virtual void accept(IRenderer* renderer) const = 0;
};
