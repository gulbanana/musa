#pragma once
#include "RootNode.h"

class SceneImpl;

//scene graph based on game entities as nodes
class EntityGraph
{
	std::shared_ptr<RootNode> _root;

public:
	EntityGraph();

	//adds a node to the scene graph
	void add_entity(std::shared_ptr<IGraphNode> entity);

	//returns a "flat" copy of the scene graph in traversal order
	std::vector<std::shared_ptr<IEntity>> entity_list();

	//returns a walkable copy of the scene graph
	//XXX this may not be needed, as systems can access it through their components
	RootNode* entity_tree();
};