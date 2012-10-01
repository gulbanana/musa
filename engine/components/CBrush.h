#pragma once
#include "IComponent.h"

class CBrush : public Identified<IComponent, CID::Brush>
{
public:
	Color4F color;
	CBrush(Color4F c) : color(c) {}
	CBrush(float r, float g, float b, float a = 1.f) : color(r, g, b, a) {}
};

