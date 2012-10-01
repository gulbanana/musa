#pragma once
#include <memory>
#include <vector>
#include <engine/core.h>

class CPhysics : public Identified<IComponent, CID::Physics>
{
public:
	bool solid;
	bool can_collide;

	std::vector<std::shared_ptr<IEntity>> collisions;
	CPhysics(bool subject, bool object) : can_collide(subject), solid(object), collisions() {}
};

