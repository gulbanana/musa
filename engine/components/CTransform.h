#pragma once

class CTransform : public Identified<IComponent, CMP::Transform>
{
public:
	//position data
	point translate;
	angles rotate;
	glm::vec3 scale;

	//constructors
	CTransform(coord x, coord y, coord z) :                          translate(x,y,z),    rotate(0.0, 0.0, 0.0), scale(1.0, 1.0, 1.0) {}
	CTransform(point location) :                                     translate(location), rotate(0.0, 0.0, 0.0), scale(1.0, 1.0, 1.0) {}
	CTransform(point location, angles orientation) :                 translate(location), rotate(orientation),   scale(1.0, 1.0, 1.0) {}
	CTransform(point location, angles orientation, glm::vec3 size) : translate(location), rotate(orientation),   scale(size) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CTransform(*this)); }
};

