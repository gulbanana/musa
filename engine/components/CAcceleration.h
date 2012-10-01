#pragma once
#include "IComponent.h"

class CAcceleration : public Identified<IComponent, CID::Acceleration>
{
public:
	Vector3F vector_change;
	Vector3F rotation_change;
	
	CAcceleration(float x, float y) : vector_change(x,y,0.f), rotation_change(0.f,0.f,0.f) {}
	CAcceleration(float x, float y, float z) : vector_change(x,y,z), rotation_change(0.f,0.f,0.f) {}
	CAcceleration(Vector3F vector_change) : vector_change(vector_change), rotation_change(0.f,0.f,0.f) {}
	CAcceleration(Vector3F vector_change, Vector3F rotation_change) : vector_change(vector_change), rotation_change(rotation_change) {}
};

