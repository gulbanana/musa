#pragma once

class CVelocity : public Identified<IComponent, CMP::Velocity>
{
public:
	point vector;
	angles rotation;
	
	CVelocity(coord x, coord y) : vector(x,y,(coord)0.0), rotation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CVelocity(coord x, coord y, coord z) : vector(x,y,z), rotation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CVelocity(point vector) : vector(vector), rotation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CVelocity(point vector, degrees zRotation) : vector(vector), rotation((degrees)0.0,(degrees)0.0,zRotation) {}
	CVelocity(point vector, angles rotation) : vector(vector), rotation(rotation) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CVelocity(*this)); }
};

