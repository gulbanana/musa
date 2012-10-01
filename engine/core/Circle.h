#pragma once
#include "IRenderable.h"
#include "IBounded.h"

class Circle : public IRenderable, public IBounded<Rect4F>
{
	float radius;
public:
	Circle(float r) : radius(r) {}
	void accept(IRenderer* renderer) override { renderer->visit(this); }
	Rect4F accept(IBounder<Rect4F>* bounder) override { return bounder->visit(this); }
};