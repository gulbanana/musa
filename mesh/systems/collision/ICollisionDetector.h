#pragma once
#include <core/framework.h>

class ICollisionDetector
{
public:
	virtual ~ICollisionDetector() {}
	virtual bool collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target) = 0;
};

