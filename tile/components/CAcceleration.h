#pragma once
#include <core/framework.h>
#include <tile/types.h>

class CAcceleration final : public Identified<IComponent, CMP::Acceleration>
{
public:
	vec2 vector_change;
	angle versor_change;
	
	CAcceleration(dist x, dist y)            : vector_change(x,y),    versor_change(0) {}
	CAcceleration(vec2 vector)               : vector_change(vector), versor_change(0) {}
	CAcceleration(vec2 vector, angle versor) : vector_change(vector), versor_change(versor) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CAcceleration(*this)); }
};

namespace std
{
	string to_string(CAcceleration a)
	{
		return string("Acceleration{") 
			+ "vector_change: " + to_string(a.vector_change) + ","
			+ "versor_change: " + to_string(a.versor_change) 
		+ "}";
	}
}