#pragma once

class CTransform : public Identified<IComponent, CMP::Transform>
{
public:
	//position data
	point translate;
	rotation rotate;
	lnseg scale;

	//constructors
	CTransform(coord x, coord y, coord z) :                     translate(x,y,z),    rotate(constants::forward_orientation), scale(1.0, 1.0, 1.0) {}
	CTransform(point location) :                                translate(location), rotate(constants::forward_orientation), scale(1.0, 1.0, 1.0) {}
	CTransform(point location, rotation orientation) :             translate(location), rotate(orientation),             scale(1.0, 1.0, 1.0) {}
	CTransform(point location, rotation orientation, lnseg size) : translate(location), rotate(orientation),             scale(size) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CTransform(*this)); }

	lnseg direction_vector();
};

