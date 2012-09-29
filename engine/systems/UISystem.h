#pragma once
#include "../GameState.h"
#include "ISystem.h"

class UISystem : public ISystem
{
	std::shared_ptr<GameState> state;
	void print(std::string output, float x, float y);
public:
	UISystem(std::shared_ptr<GameState> s);
	void on_frame() override;
};

