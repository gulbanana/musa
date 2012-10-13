#pragma once
#include <memory>
#include <vector>
#include <string>
#include <engine/core.h>
#include <engine/scene.h>
#include "Settings.h"

class EngineImpl;

class Engine
{
	EngineImpl* _pimpl;

public:
	Engine(Settings& settings, std::vector<std::unique_ptr<ISystem>> customLogic);
	~Engine();

	void play();
	void load_scene(EntityGraph& level);
};

#define main SDL_main