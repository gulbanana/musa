#pragma once
#include <engine/core.h>
#include "IRenderable.h"
#include "IBounded.h"

struct CircleMesh : public IRenderable, public IBounded<Rect4F>
{
	float radius;
	CircleMesh(float r) : radius(r) {}
	void accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) override 
	{ 
		renderer->visit(this, brush, position, orientation); 
	}
	Rect4F accept(IBounder<Rect4F>* bounder) override { return bounder->visit(this); }
};