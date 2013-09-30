#pragma once
#include <core/framework.h>
#include <mesh/geometry.h>

// a modelobject renderer node 
class CRenderable : public Identified<CRenderable,IComponent>
{
public:
	IRenderable* geometry;

	CRenderable(IRenderable* geometry) : geometry(geometry) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CRenderable(*this)); }
};

