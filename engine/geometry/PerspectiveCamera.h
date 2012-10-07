#pragma once
#include "ITransform.h"

struct PerspectiveCamera : public ITransform
{
	degrees* fov_override;

	PerspectiveCamera() : fov_override(nullptr) {}
	PerspectiveCamera(degrees fov) : fov_override(new degrees(fov)) {}
	~PerspectiveCamera() { if (fov_override != nullptr) delete fov_override; }

	virtual void accept(IRenderer* renderer) const override { renderer->morph(this); }
	virtual void eject(IRenderer* renderer) const override { renderer->unmorph(this); }
};