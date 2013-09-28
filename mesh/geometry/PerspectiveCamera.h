#pragma once
#include "IRenderable.h"

struct PerspectiveCamera : public IRenderable
{
	ScaleMethod widescreen;
	angle fov;
	coord dof;

	PerspectiveCamera(ScaleMethod widescreen, angle fieldOfView, coord depthOfField) : widescreen(widescreen), fov(fieldOfView), dof(depthOfField) {}

	virtual void accept_enter(IRenderer* renderer) const override { renderer->visit_enter(this); }
	virtual void accept_leave(IRenderer* renderer) const override { renderer->visit_leave(this); }
	//XXX make this contain the precalculated frustum
	virtual box6 bounds() const final     { return box6(0,0,0,0,0,0); } 
	virtual size_t polygons() const final { return 0; }
	virtual bool is_camera() const final  { return true; }
};