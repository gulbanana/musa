#pragma once
#include "ITransform.h"

struct PerspectiveCamera : public ITransform
{
	ScaleMethod widescreen;
	bool natural_fov;
	degrees fov_override;

	PerspectiveCamera(ScaleMethod widescreen) : widescreen(widescreen), natural_fov(true) {}
	PerspectiveCamera(ScaleMethod widescreen, degrees fov) : widescreen(widescreen), natural_fov(false), fov_override(fov) {}

	virtual void accept(IRenderer* renderer) const override { renderer->morph(this); }
	virtual void eject(IRenderer* renderer) const override { renderer->unmorph(this); }
};