//each Scene component represents an independent scene graph to be rendered 
//renderers handle scenes as a unit, walking their tree rather than 
//processing a flat entity list

#pragma once
#include <memory>
#include <engine/core.h>
#include <engine/geometry.h>

class CScene : public Identified<IComponent, CMP::Scene>
{
public:
	int flags;

	CScene() {}
};

