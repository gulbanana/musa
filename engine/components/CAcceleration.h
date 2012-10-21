#pragma once

class CAcceleration final : public Identified<IComponent, CMP::Acceleration>
{
public:
	point vector_change;
	angle rotation_change;
	
	CAcceleration(coord x, coord y, coord z)     : vector_change(x,y,z),  rotation_change(0, 0, 0, 0) {}
	CAcceleration(point vector)                  : vector_change(vector), rotation_change(0,0,0,0) {}
	CAcceleration(point vector, angle rotation)  : vector_change(vector), rotation_change(rotation) {}
	CAcceleration(point vector, eulers rotation) : vector_change(vector), rotation_change(rotation) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CAcceleration(*this)); }
};

