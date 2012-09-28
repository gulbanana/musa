#pragma once
#include "ISystem.h"

class MotionSystem : public ISystem
{
	float levelWidth;
	float levelHeight;

public:
	MotionSystem(float boundsX, float boundsY);

	std::vector<CID> required_components() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
};

