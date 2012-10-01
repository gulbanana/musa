#pragma once
#include "IRenderable.h"
#include "IBounded.h"

class Rectangle : public IRenderable, IBounded<Rect4F>
{
	friend class IRenderer;
	friend class IBounder<Rect4F>;
	Rect4F bounds;
public:
	//general rect constructor
	Rectangle(Rect4F b) : bounds(b) {}
	Rectangle(float x1, float y1, float x2, float y2) : bounds(Rect4F(x1, y1, x2, y2)) {}
	//square constructor
	Rectangle(float radius) : bounds(-radius, -radius, radius, radius) {}	
	//visitors
	void accept(IRenderer* renderer) override { renderer->visit(this); }
	Rect4F accept(IBounder<Rect4F>* bounder) override { return bounder->visit(this); }
};