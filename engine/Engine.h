#pragma once
#include "Settings.h"

class EngineImpl;

class Engine
{
	EngineImpl* _pimpl;

public:
	Engine(Settings& settings, std::vector<std::unique_ptr<ISystem>> customLogic);
	~Engine();

	void play();
	void load_scene(std::vector<std::shared_ptr<IEntity>> level);
};

#define main SDL_main