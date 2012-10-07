#pragma once
#include "ITransform.h"

struct OrthographicCamera : public ITransform
{
	coord depth;
	OrthographicCamera(coord depth) : depth(depth) {}

	virtual void accept(IRenderer* renderer) const override { renderer->morph(this); }
	virtual void eject(IRenderer* renderer) const override { renderer->unmorph(this); }
};