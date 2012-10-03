#pragma once
#include <engine/core.h>

class CAcceleration : public Identified<IComponent, CMP::Acceleration>
{
public:
	Vec3<coord> vector_change;
	Vec3<degrees> rotation_change;
	
	CAcceleration(coord x, coord y) : vector_change(x,y,(coord)0), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(coord x, coord y, coord z) : vector_change(x,y,z), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(Vec3<coord> vector_change) : vector_change(vector_change), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(Vec3<coord> vector_change, Vec3<degrees> rotation_change) : vector_change(vector_change), rotation_change(rotation_change) {}
};

