#pragma once
#include "IRenderable.h"

struct PerspectiveCamera : public IRenderable
{
	ScaleMethod widescreen;
	degrees fov;
	coord dof;

	PerspectiveCamera(ScaleMethod widescreen, degrees fieldOfView, coord depthOfField) : widescreen(widescreen), fov(fieldOfView), dof(depthOfField) {}

	virtual void accept_enter(IRenderer* renderer) const override { renderer->visit_enter(this); }
	virtual void accept_leave(IRenderer* renderer) const override { renderer->visit_leave(this); }
	//XXXmake this contain the precalculated frustum
	virtual box6 bounds() const override     { return box6(0,0,0,0,0,0); } 
	virtual size_t polygons() const override { return 0; }
};