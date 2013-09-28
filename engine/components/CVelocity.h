#pragma once

class CVelocity : public Identified<IComponent, CMP::Velocity>
{
public:
	vec2 vector;
	angle versor;
	
	CVelocity()                          : vector(vec2::ZERO), versor(0) {}
	CVelocity(dist x, dist y)            : vector(vec2(x,y)),  versor(0) {}
	CVelocity(vec2 vector)               : vector(vector),     versor(0) {}
	CVelocity(vec2 vector, angle versor) : vector(vector),     versor(versor) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CVelocity(*this)); }
};