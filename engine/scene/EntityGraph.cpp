#include <engine/core.h>
#include <algorithm>
#include "EntityGraph.h"
#include "LambdaWalker.h"
#include "LeafNode.h"
using namespace std;

//todo: constructors which load a level from structured data!
EntityGraph::EntityGraph() : _root(make_shared<RootNode>(AutonomousEntityFactory().create())) {}

void EntityGraph::add_entity(shared_ptr<IEntity> entity, bool branch)
{
	if (branch)
	{
		_root->children.emplace_back(new BranchNode(entity));
	}
	else
	{
		_root->children.emplace_back(new LeafNode(entity));
	}
}

RootNode* EntityGraph::entity_tree()
{
	return _root.get();
}

vector<shared_ptr<IEntity>> EntityGraph::entity_list()
{
	vector<shared_ptr<IEntity>> refs;
	refs.push_back(_root->_entity);

	LambdaWalker vecBuilder(
		[](LeafNode*){}, 
		[&](BranchNode* b)
		{ 
			for (auto& child : b->children)
			{
				refs.push_back(child->_entity);
			}
		}
	);

	vecBuilder.visit(_root.get());

	return refs;
}