#pragma once
#include <vector>
#include <engine/core.h>
#include "IRenderable.h"

//"Face-Vertex" mesh- small storage, fast rendering, no dynamic edits
struct FVMesh : public IRenderable
{
	struct Vertex : Vector3F
	{
		std::vector<int> adjacent;
	};

	std::vector<Vector3F> vertices;
	std::vector<Vector3F> faces;

	FVMesh(Vector3F vertexList[]) {}
    virtual ~FVMesh() {}

	void accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) const override;
	Box6F bounds() const override;
};

