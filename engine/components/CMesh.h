#pragma once
#include <memory>
#include <engine/geometry.h>
#include "IComponent.h"

class CMesh : public Identified<IComponent, CID::Mesh>
{
public:
	std::shared_ptr<IRenderable> geometry;
	CMesh(std::shared_ptr<IRenderable> g) : geometry(g) {}
};

