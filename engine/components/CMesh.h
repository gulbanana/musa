#pragma once
#include <engine/geometry.h>

// a modelobject renderer node 
class CMesh : public Identified<IComponent, CMP::Mesh>
{
public:
	IModel* geometry;
	CMesh(IModel* geometry) : geometry(geometry) {}
};

