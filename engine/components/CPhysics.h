#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"
#include "../entities/IEntity.h"

class CPhysics : public Identified<IComponent, CID::Physics>
{
public:
	bool reactive;
	bool solid;
	std::vector<std::shared_ptr<IEntity>> collisions;
	CPhysics(bool subject, bool object) : reactive(subject), solid(object), collisions() {}
};

