#pragma once
#include <vector>
#include "../core.h"
#include "IDrawable.h"

class Polygon : public IDrawable
{
	std::vector<Vector3F> vertices;
public:
	Polygon(Vector3F vertexList[]);
	Polygon(Vector2F vertexList[]);
	void draw() override;
};

