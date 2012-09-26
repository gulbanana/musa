#pragma once
#include <SFML/Graphics.hpp>
#include "ISystem.h"

class MotionSystem : public ISystem
{
public:
	void frame() override;
	std::vector<std::string> required_components() override;
};

