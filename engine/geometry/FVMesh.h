#pragma once
#include <vector>
#include <engine/core.h>
#include "IRenderable.h"

//"Face-Vertex" mesh- small storage, fast rendering, no dynamic edits. Triangular faces.
struct FVMesh : public IRenderable
{
	std::vector<Vec3<coord>> vertices;
	std::vector<int> faces;
	std::vector<Vec2<coord>> triangles;

	FVMesh(Vec3<coord> vertexList[]) {}
    virtual ~FVMesh() {}

	void accept(IRenderer* renderer, Color4F brush, Vec3<coord> position, Vec3<degrees> orientation) const override;
	Box6<coord> bounds() const override;
};

