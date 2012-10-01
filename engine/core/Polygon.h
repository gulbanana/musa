#pragma once
#include <vector>
#include "IRenderable.h"
#include "IBounded.h"

class Polygon : public IRenderable, public IBounded<Rect4F>
{
	friend class IRenderer;
	friend class IBounder<Rect4F>;
	std::vector<Vector3F> vertices;
public:
	Polygon::Polygon(Vector3F vertexList[]) {}
	Polygon::Polygon(Vector2F vertexList[]) {}
	void accept(IRenderer* renderer) override { renderer->visit(this); }
	Rect4F accept(IBounder<Rect4F>* bounder) override { return bounder->visit(this); }
};

