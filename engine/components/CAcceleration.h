#pragma once

class CAcceleration : public Identified<IComponent, CMP::Acceleration>
{
public:
	point vector_change;
	angles rotation_change;
	
	CAcceleration(coord x, coord y) : vector_change(x,y,(coord)0), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(coord x, coord y, coord z) : vector_change(x,y,z), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(point vector_change) : vector_change(vector_change), rotation_change((degrees)0,(degrees)0,degrees(0)) {}
	CAcceleration(point vector_change, angles rotation_change) : vector_change(vector_change), rotation_change(rotation_change) {}
};

