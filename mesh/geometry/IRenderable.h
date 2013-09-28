#pragma once
#include <mesh/types.h>
#include "IRenderer.h"

class IRenderable
{
public:
	virtual ~IRenderable() {}
	
	virtual void accept_enter(IRenderer* renderer) const = 0;
	virtual void accept_leave(IRenderer* renderer) const = 0;

	virtual box6 bounds() const = 0;
	virtual size_t polygons() const = 0;
	virtual bool is_camera() const = 0;
};
