#pragma once
#include "IRenderable.h"
#include "ScaleMethod.h"

/* 
A 5x5x5 orthographic camera views a 5x5x5 region in front of it, origin-centred like a modelobject
top down:
	.....
	.....
	.....>camera
	.....
	.....
from behind:
	.....
	.....
	..*..
	.....
	.....
This is not a typical orthographic projection but is designed to be attached to an entity and positioned like a frustum camera.
*/
struct OrthographicCamera : public IRenderable
{
	box6 range;
	ScaleMethod widescreen;

	OrthographicCamera(box6 bounds, ScaleMethod widescreen = ScaleMethod::HorPlus) : range(bounds), widescreen(widescreen) {}

	virtual void accept_enter(IRenderer* renderer) const override { renderer->visit_enter(this); }
	virtual void accept_leave(IRenderer* renderer) const override { renderer->visit_leave(this); }
	virtual box6 bounds() const override { return range; }
	virtual size_t polygons() const override { return 0; }
};