#pragma once
#include "ITransform.h"
#include "ScaleMethod.h"

struct OrthographicCamera : public ITransform
{
	Box6<coord> range;
	ScaleMethod widescreen;

	OrthographicCamera(Box6<coord> bounds, ScaleMethod widescreen = ScaleMethod::HorPlus) : range(bounds), widescreen(widescreen) {}

	virtual void accept(IRenderer* renderer) const override { renderer->morph(this); }
	virtual void eject(IRenderer* renderer) const override { renderer->unmorph(this); }
};