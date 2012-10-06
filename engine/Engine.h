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
	Engine(std::string title, int width, int height);

	void play();
	void load_scene(Scene* level, std::unique_ptr<ISystem>&& logic);
};

#define main SDL_main