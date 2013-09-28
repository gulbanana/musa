#pragma once
#include "RootNode.h"
#include "BranchNode.h"

class SceneImpl;

//multi-camera scene graph - just a useful view of the entities
class SceneGraph
{
	std::unique_ptr<RootNode> _root;

public:
	SceneGraph();

	//creates a new branch
	void add_branch(std::shared_ptr<IEntity> entity);

	//adds a node to every branch of the scene graph
	void add_leaf(std::shared_ptr<IEntity> entity);

	//returns a "flat" copy of the scene graph in traversal order
	std::vector<IGraphNode*> node_list();

	//returns a walkable copy of the scene graph
	IGraphNode* node_tree();
};