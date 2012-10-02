#pragma once
#include <memory>
#include <engine/core.h>
#include <engine/geometry.h>

class CMesh : public Identified<IComponent, CMP::Mesh>
{
public:
	std::unique_ptr<IRenderable> geometry;
	CMesh(std::unique_ptr<IRenderable> g) : geometry(std::move(g)) {}
};

