#pragma once
#include <engine/core.h>
#include "IRenderable.h"
#include "IBounded.h"

struct RectangularPrismMesh : public IRenderable, public IBounded<Rect4F>, public IBounded<Box6F>
{
	Box6F bounds;
	//general rect constructor
	RectangularPrismMesh(Box6F b) : bounds(b) {}
	RectangularPrismMesh(float x1, float y1, float z1, float x2, float y2, float z2) : bounds(Box6F(x1, y1, z1, x2, y2, z2)) {}
	//square constructor
	RectangularPrismMesh(float radius) : bounds(-radius, -radius, -radius, radius, radius, radius) {}	
	//visitors
	void accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) override { 
		renderer->visit(this, brush, position, orientation); 
	}
	Rect4F accept(IBounder<Rect4F>* bounder) override { return bounder->visit(this); }
	Box6F accept(IBounder<Box6F>* bounder) override { return bounder->visit(this); }
};