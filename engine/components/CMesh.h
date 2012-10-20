#pragma once
#include <engine/geometry.h>

// a modelobject renderer node 
class CMesh : public Identified<IComponent, CMP::Mesh>
{
public:
	IModel* geometry;

	CMesh(IModel* geometry) : geometry(geometry) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CMesh(*this)); }
};

