#pragma once
#include <memory>
#include <engine/core.h>
#include <engine/geometry.h>

// a renderer node - could be meshes, transforms, shaders, anything that goes through the renderer
class CNode : public Identified<IComponent, CMP::Node>
{
public:
	IRenderable* geometry;
	CNode(IRenderable* geometry) : geometry(geometry) {}
};

