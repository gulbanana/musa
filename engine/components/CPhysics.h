#pragma once

class CPhysics : public Identified<IComponent, CMP::Physics>
{
public:
	bool solid;
	bool can_collide;

	std::vector<std::shared_ptr<IEntity>> collisions;
	CPhysics(bool subject, bool object) : can_collide(subject), solid(object), collisions() {}
};

