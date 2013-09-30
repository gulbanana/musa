#pragma once
#include <core/framework.h>

class CPhysics : public Identified<CPhysics,IComponent>
{
public:
	bool solid;
	bool can_collide;

	std::vector<std::shared_ptr<IEntity>> collisions;

	CPhysics(bool subject, bool object) : can_collide(subject), solid(object), collisions() {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CPhysics(*this)); }
};

namespace std
{
	string to_string(CPhysics p)
	{
		return string("Physics{") 
			+ "solid: " + to_string(p.solid) + ","
			+ "can_collide: " + to_string(p.can_collide) 
		+ "}";
	}
}