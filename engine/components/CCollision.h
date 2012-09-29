#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"
#include "../entities/IEntity.h"

class CCollision : public IComponent
{
	IDENTIFIED(IComponent, Collision);
	bool subject;
	bool object;
	std::vector<std::shared_ptr<IEntity>> collisions;
	CCollision(bool isSubject, bool isObject) : subject(isSubject), object(isObject), collisions() {}
};

