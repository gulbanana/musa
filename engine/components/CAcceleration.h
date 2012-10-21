#pragma once

class CAcceleration final : public Identified<IComponent, CMP::Acceleration>
{
public:
	point vector_change;
	angles rotation_change;
	
	CAcceleration(coord x, coord y) : vector_change(x,y,(coord)0), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(coord x, coord y, coord z) : vector_change(x,y,z), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(point vector_change) : vector_change(vector_change), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(point vector_change, angles rotation_change) : vector_change(vector_change), rotation_change(rotation_change) {}

	std::vector<CMP> required_components() const { return std::vector<CMP>(); }
	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CAcceleration(*this)); }
};

