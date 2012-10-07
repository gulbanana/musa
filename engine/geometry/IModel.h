#pragma once
#include "IRenderer.h"

class IModel
{
public:
	virtual ~IModel() {}
	
	virtual void accept(IRenderer* renderer) const = 0;

	virtual Box6<coord> bounds() const = 0;
	virtual size_t polygons() const = 0;
};
