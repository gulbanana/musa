#pragma once
#include <engine/geometry.h>

// a modelobject renderer node 
class CModel : public Identified<IComponent, CMP::Model>
{
public:
	IRenderable* geometry;

	CModel(IRenderable* geometry) : geometry(geometry) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CModel(*this)); }
};

