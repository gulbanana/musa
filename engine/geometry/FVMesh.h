#pragma once
#include <vector>
#include <engine/core.h>
#include "IRenderable.h"

//"Face-Vertex" mesh- small storage, fast rendering, no dynamic edits. Triangular faces.
struct FVMesh : public IRenderable
{
	std::vector<Vector3F> vertices;
	std::vector<int> faces;
	std::vector<Vector2F> triangles;

	FVMesh(Vector3F vertexList[]) {}
    virtual ~FVMesh() {}

	void accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) const override;
	Box6F bounds() const override;
};

