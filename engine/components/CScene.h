//each Scene component represents an independent scene graph to be rendered 
//renderers handle scenes as a unit, walking their tree rather than 
//processing a flat entity list

#pragma once
#include <engine/geometry.h>

class CScene : public Identified<IComponent, CMP::Scene>
{
public:
	int flags;
	//camera??

	CScene() {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CScene(*this)); }
};

