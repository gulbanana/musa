#pragma once
#include "ITransform.h"

struct PerspectiveCamera : public ITransform
{
	ScaleMethod widescreen;
	degrees fov;
	coord dof;

	PerspectiveCamera(ScaleMethod widescreen, degrees fieldOfView, coord depthOfField) : widescreen(widescreen), fov(fieldOfView), dof(depthOfField) {}

	virtual void accept(IRenderer* renderer) const override { renderer->morph(this); }
	virtual void eject(IRenderer* renderer) const override { renderer->unmorph(this); }
};