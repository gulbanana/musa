#pragma once

class CVelocity : public Identified<IComponent, CMP::Velocity>
{
public:
	point vector;
	angle rotation;
	
	CVelocity()                              : vector(),       rotation(0,0,0,0) {}
	CVelocity(coord x, coord y, coord z)     : vector(x,y,z),  rotation(0,0,0,0) {}
	CVelocity(point vector)                  : vector(vector), rotation(0,0,0,0) {}
	CVelocity(point vector, angle rotation)  : vector(vector), rotation(rotation) {}
	CVelocity(point vector, eulers rotation) : vector(vector), rotation(rotation) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CVelocity(*this)); }
};

