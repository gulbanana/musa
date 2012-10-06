#pragma once
#include <memory>
#include <vector>
#include <string>
#include <engine/core.h>
#include "Scene.h"

class EngineImpl;

class Engine
{
	EngineImpl* _pimpl;

public:
	Engine(std::unique_ptr<ISystem>&& logic, std::string title, int width, int height);
	~Engine();

	void play();
	void load_scene(EntityGraph* level);
};

#define main SDL_main