#pragma once

class CPosition : public Identified<IComponent, CMP::Position>
{
public:
	//position data
	Vec3<coord> location;
	Vec3<coord> previous_location;
	Vec3<degrees> orientation;

	//constructors
	CPosition(coord x, coord y) : location(x,y,(coord)0.0), previous_location(x,y,(coord)0.0), orientation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CPosition(coord x, coord y, coord z) : location(x,y,z), previous_location(x,y,z), orientation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CPosition(Vec3<coord> location) : location(location), previous_location(location), orientation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CPosition(Vec3<coord> location, Vec3<degrees> orientation) : location(location), previous_location(location), orientation(orientation) {}
};

