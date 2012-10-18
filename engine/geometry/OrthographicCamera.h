#pragma once
#include "ITransform.h"
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
struct OrthographicCamera : public ITransform
{
	box6 range;
	ScaleMethod widescreen;

	OrthographicCamera(box6 bounds, ScaleMethod widescreen = ScaleMethod::HorPlus) : range(bounds), widescreen(widescreen) {}

	virtual void accept(IRenderer* renderer) const override { renderer->morph(this); }
	virtual void eject(IRenderer* renderer) const override { renderer->unmorph(this); }
};