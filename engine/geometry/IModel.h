#pragma once
#include "IRenderable.h"

class IModel : public IRenderable
{
public:
	virtual ~IModel() {}
	
	virtual box6 bounds() const = 0;
	virtual size_t polygons() const = 0;
};
