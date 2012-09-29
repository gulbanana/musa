#pragma once
#include "ICollisionDetector.h"

class RectIntersectionDetector : public ICollisionDetector
{
public:
	bool collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target) override;
};

