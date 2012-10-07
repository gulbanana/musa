#pragma once
#include "ITransform.h"

struct PerspectiveCamera : public ITransform
{
	ScaleMethod widescreen;
	degrees fov;

	PerspectiveCamera(ScaleMethod widescreen) : widescreen(widescreen), fov(60) {}
	PerspectiveCamera(ScaleMethod widescreen, degrees fov) : widescreen(widescreen), fov(fov) {}

	virtual void accept(IRenderer* renderer) const override { renderer->morph(this); }
	virtual void eject(IRenderer* renderer) const override { renderer->unmorph(this); }
};