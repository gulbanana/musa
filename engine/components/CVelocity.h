#pragma once

class CVelocity : public Identified<IComponent, CMP::Velocity>
{
public:
	Vec3<coord> vector;
	Vec3<degrees> rotation;
	
	CVelocity(coord x, coord y) : vector(x,y,(coord)0.0), rotation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CVelocity(coord x, coord y, coord z) : vector(x,y,z), rotation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CVelocity(Vec3<coord> vector) : vector(vector), rotation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CVelocity(Vec3<coord> vector, degrees zRotation) : vector(vector), rotation((degrees)0.0,(degrees)0.0,zRotation) {}
	CVelocity(Vec3<coord> vector, Vec3<degrees> rotation) : vector(vector), rotation(rotation) {}
};

