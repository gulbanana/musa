#pragma once
#include <engine/core.h>
#include "IRenderable.h"
#include "IBounded.h"

//this can't be called Rectangle unless it's in a namespace, because there is a windows api function by that name
struct RectangleMesh : public IRenderable, public IBounded<Rect4F>
{
	Rect4F bounds;
	//general rect constructor
	RectangleMesh(Rect4F b) : bounds(b) {}
	RectangleMesh(float x1, float y1, float x2, float y2) : bounds(Rect4F(x1, y1, x2, y2)) {}
	//square constructor
	RectangleMesh(float radius) : bounds(-radius, -radius, radius, radius) {}	
	//visitors
	void accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) override { 
		renderer->visit(this, brush, position, orientation); 
	}
	Rect4F accept(IBounder<Rect4F>* bounder) override { return bounder->visit(this); }
};