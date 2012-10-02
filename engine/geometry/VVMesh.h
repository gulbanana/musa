#pragma once
#include <vector>
#include <engine/core.h>
#include "IRenderable.h"

//"Vertex-Vertex" mesh- most minimal storage, requires traversal to calculate faces
struct VVMesh : public IRenderable
{
	//data
	struct Vertex : Vector3F
	{
		std::vector<int> adjacent;
		Vertex(float x, float y, float z) : Vector3F(x, y, z), adjacent() {}
	};
	std::vector<Vertex> vertices;

	//api
	VVMesh(std::vector<Vertex>&&);
	void accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) const override;
	Box6F bounds() const override;

private:
	Box6F bounds_cache;
};

