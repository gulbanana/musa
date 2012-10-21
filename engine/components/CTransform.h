#pragma once

class CTransform : public Identified<IComponent, CMP::Transform>
{
public:
	//position data
	point translate;
	angle rotate;
	lnseg scale;

	//constructors
	CTransform(coord x, coord y, coord z) :                     translate(x,y,z),    rotate(maths::forward_rotation), scale(1.0, 1.0, 1.0) {}
	CTransform(point location) :                                translate(location), rotate(maths::forward_rotation), scale(1.0, 1.0, 1.0) {}
	CTransform(point location, angle orientation) :             translate(location), rotate(orientation),             scale(1.0, 1.0, 1.0) {}
	CTransform(point location, angle orientation, lnseg size) : translate(location), rotate(orientation),             scale(size) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CTransform(*this)); }
};

