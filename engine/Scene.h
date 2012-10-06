#pragma once
#include <memory>
#include <engine/core.h>

class SceneImpl;

class Scene
{
	std::vector<std::shared_ptr<IEntity>> _nodes;

public:
	Scene();

	//adds a node to the scene graph
	void add_entity(std::shared_ptr<IEntity> entity);

	//returns a "flat" copy of the scene graph in traversal order
	std::vector<std::weak_ptr<IEntity>> entities();
};