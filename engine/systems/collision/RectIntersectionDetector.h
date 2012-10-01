#pragma once
#include "ICollisionDetector.h"
#include "Bounder2D.h"

class RectIntersectionDetector : public ICollisionDetector
{
	Bounder2D _bounder;
public:
	bool collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target) override;
};

