#pragma once
#include "IMaterial.h"

struct SolidColourBrush : public IMaterial
{
	Colour4F colour;

	SolidColourBrush(Colour4F c) : colour(c) {}

	virtual void accept(IRenderer* renderer) const override
	{ 
		renderer->paint(this); 
	}
};