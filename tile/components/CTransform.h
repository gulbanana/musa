#pragma once
#include <core/framework.h>
#include <tile/types.h>

class CTransform : public Identified<CTransform, IComponent>
{
public:
	//position data
	point translate;
	angle rotate;

	//constructors
	CTransform(coord x, coord y, coord z) :         translate(x,y,z),    rotate(0) {}
	CTransform(point location) :                    translate(location), rotate(0) {}
	CTransform(point location, angle orientation) : translate(location), rotate(orientation) {}
	CTransform(point location, dir orientation) :   translate(location), rotate((angle)orientation) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CTransform(*this)); }
};

namespace std
{
	string to_string(CTransform t);
}