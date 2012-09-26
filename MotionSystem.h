#pragma once
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class MotionSystem : public ISystem
{
public:
	std::vector<std::string> required_components() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
};

