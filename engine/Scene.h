#pragma once
#include <memory>
#include <engine/core.h>

class SceneImpl;

class Scene
{
	SceneImpl* _pimpl;

public:
	Scene();

	void add_entity(std::shared_ptr<IEntity> entity);
	void add_system(std::unique_ptr<ISystem>&& system);
	void frame();
};