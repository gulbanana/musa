#pragma once
#include "ISystem.h"

class UISystem : public ISystem
{
	//UI information
	int& fps;

	void print(std::string output, float x, float y);

public:
	UISystem(int& fpsCounter);
	void on_frame() override;
};

