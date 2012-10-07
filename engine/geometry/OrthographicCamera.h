#pragma once
#include "ITransform.h"

struct OrthographicCamera : public ITransform
{
	Box6<coord> visible_world;
	OrthographicCamera(Box6<coord> bounds) : visible_world(bounds) {}

	virtual void accept(IRenderer* renderer) const override { renderer->morph(this); }
	virtual void eject(IRenderer* renderer) const override { renderer->unmorph(this); }
};