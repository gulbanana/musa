#pragma once
#include <engine/geometry.h>

// a modelobject renderer node 
class CRenderable : public Identified<IComponent, CMP::Renderable>
{
public:
	IRenderable* geometry;

	CRenderable(IRenderable* geometry) : geometry(geometry) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CRenderable(*this)); }
};

namespace std
{
	string to_string(CRenderable p)
	{
		return string("Renderable{}");
	}
}