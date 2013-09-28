#pragma once

class CAcceleration final : public Identified<IComponent, CMP::Acceleration>
{
public:
	point vector_change;
	rotation versor_change;
	
	CAcceleration(coord x, coord y, coord z)     : vector_change(x,y,z),  versor_change(1,0,0,0) {}
	CAcceleration(point vector)                  : vector_change(vector), versor_change(1,0,0,0) {}
	CAcceleration(point vector, rotation versor)  : vector_change(vector), versor_change(versor) {}
	CAcceleration(point vector, eulers versor) : vector_change(vector), versor_change(versor) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CAcceleration(*this)); }
};

