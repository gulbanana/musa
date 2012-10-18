#pragma once
#include "IMaterial.h"

struct SolidColourBrush : public IMaterial
{
	glm::vec4 colour;

	SolidColourBrush(glm::vec4 c) : colour(c) {}

	virtual void accept(IRenderer* renderer) const override
	{ 
		renderer->paint(this); 
	}
};