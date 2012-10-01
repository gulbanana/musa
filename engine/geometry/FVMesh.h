#pragma once
#include <vector>
#include <engine/core.h>
#include "IRenderable.h"
#include "IBounded.h"

//"Face-Vertex" mesh- small storage, fast rendering, no dynamic edits
struct FVMesh : public IRenderable, public IBounded<Rect4F>, public IBounded<Box6F>
{
	std::vector<Vector3F> vertices;
	FVMesh::FVMesh(Vector3F vertexList[]) {}
	void accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) override 
	{ 
		renderer->visit(this, brush, position, orientation); 
	}
	Rect4F accept(IBounder<Rect4F>* bounder) override { return bounder->visit(this); }
	Box6F accept(IBounder<Box6F>* bounder) override { return bounder->visit(this); }
};

