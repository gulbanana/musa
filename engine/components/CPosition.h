#pragma once

class CPosition : public Identified<IComponent, CMP::Position>
{
public:
	//position data
	point location;
	point previous_location;
	angles orientation;

	//constructors
	CPosition(coord x, coord y) : location(x,y,(coord)0.0), previous_location(x,y,(coord)0.0), orientation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CPosition(coord x, coord y, coord z) : location(x,y,z), previous_location(x,y,z), orientation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CPosition(point location) : location(location), previous_location(location), orientation((degrees)0.0,(degrees)0.0,(degrees)0.0) {}
	CPosition(point location, angles orientation) : location(location), previous_location(location), orientation(orientation) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CPosition(*this)); }
};

