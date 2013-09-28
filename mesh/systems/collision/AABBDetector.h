#pragma once
#include "ICollisionDetector.h"

class AABBDetector : public ICollisionDetector
{
public:
	bool collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target) override;
};

