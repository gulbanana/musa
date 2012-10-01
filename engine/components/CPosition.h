#pragma once
#include <engine/core.h>

class CPosition : public Identified<IComponent, CID::Position>
{
public:
	//position data
	Vector3F location;
	Vector3F previous_location;
	Vector3F orientation;

	//constructors
	CPosition(float x, float y) : location(x,y,0.f), previous_location(x,y,0.f), orientation(0.f,0.f,0.f) {}
	CPosition(float x, float y, float z) : location(x,y,z), previous_location(x,y,z), orientation(0.f,0.f,0.f) {}
	CPosition(Vector3F location) : location(location), previous_location(location), orientation(0.f,0.f,0.f) {}
	CPosition(Vector3F location, Vector3F orientation) : location(location), previous_location(location), orientation(orientation) {}
};

