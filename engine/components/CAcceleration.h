#pragma once

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

