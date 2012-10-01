#pragma once
#include <engine/core.h>

class CVelocity : public Identified<IComponent, CID::Velocity>
{
public:
	Vector3F vector;
	Vector3F rotation;
	
	CVelocity(float x, float y) : vector(x,y,0.f), rotation(0.f,0.f,0.f) {}
	CVelocity(float x, float y, float z) : vector(x,y,z), rotation(0.f,0.f,0.f) {}
	CVelocity(Vector3F vector) : vector(vector), rotation(0.f,0.f,0.f) {}
	CVelocity(Vector3F vector, float zRotation) : vector(vector), rotation(0.f,0.f,zRotation) {}
	CVelocity(Vector3F vector, Vector3F rotation) : vector(vector), rotation(rotation) {}
};

