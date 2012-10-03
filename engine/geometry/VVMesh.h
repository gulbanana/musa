#pragma once
#include <vector>
#include <engine/core.h>
#include "IRenderable.h"

//"Vertex-Vertex" mesh- most minimal storage, requires traversal to calculate faces
struct VVMesh : public IRenderable
{
	//data
	struct Vertex : Vec3<coord>
	{
		std::vector<int> adjacent;
		Vertex(coord x, coord y, coord z) : Vec3<coord>(x, y, z), adjacent() {}
	};
	std::vector<Vertex> vertices;

	//api
	VVMesh(std::vector<Vertex>&&);
	void accept(IRenderer* renderer, Color4F brush, Vec3<coord> position, Vec3<degrees> orientation) const override;
	Box6<coord> bounds() const override;

private:
	Box6<coord> bounds_cache;
};

