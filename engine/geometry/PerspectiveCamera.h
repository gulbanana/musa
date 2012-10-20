#pragma once
#include "IRenderable.h"

struct PerspectiveCamera : public IRenderable
{
	ScaleMethod widescreen;
	degrees fov;
	coord dof;

	PerspectiveCamera(ScaleMethod widescreen, degrees fieldOfView, coord depthOfField) : widescreen(widescreen), fov(fieldOfView), dof(depthOfField) {}

	virtual void invite(IRenderer* renderer) const override { renderer->arrive(this); }
	virtual void accept(IRenderer* renderer) const override { renderer->visit(this); }
};