#pragma once
#include <memory>
#include <engine/core.h>
#include <engine/geometry.h>

class CMesh : public Identified<IComponent, CID::Mesh>
{
public:
	std::shared_ptr<IRenderable> geometry;
	CMesh(std::shared_ptr<IRenderable> g) : geometry(g) {}
};

