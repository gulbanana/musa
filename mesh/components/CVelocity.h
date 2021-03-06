#pragma once
#include <core/framework.h>
#include <mesh/types.h>

class CVelocity : public Identified<CVelocity,IComponent>
{
public:
	point vector;
	rotation versor;
	
	CVelocity()                              : vector(),       versor(0,0,0,0) {}
	CVelocity(coord x, coord y, coord z)     : vector(x,y,z),  versor(0,0,0,0) {}
	CVelocity(point vector)                  : vector(vector), versor(0,0,0,0) {}
	CVelocity(point vector, rotation versor)  : vector(vector), versor(versor) {}
	CVelocity(point vector, eulers versor) : vector(vector), versor(versor) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CVelocity(*this)); }
};

