#include <mesh/stdafx.h>
#include <core/misc.h>
#include <algorithm>
#include "SceneGraph.h"
#include "LambdaWalker.h"
#include "LeafNode.h"
using namespace std;

//todo: constructors which load a level from structured data!
SceneGraph::SceneGraph() : _root(make_unique<RootNode>())
{
}

void SceneGraph::add_branch(shared_ptr<IEntity> entity)
{
	_root->children.emplace_back(new BranchNode(entity));
}

void SceneGraph::add_leaf(shared_ptr<IEntity> entity)
{
	for (auto& branch : _root->children)
	{
		branch->children.emplace_back(new LeafNode(entity));
	}
}

IGraphNode* SceneGraph::node_tree()
{
	return _root.get();
}

vector<IGraphNode*> SceneGraph::node_list()
{
	vector<IGraphNode*> refs;
	refs.push_back(_root.get());

	LambdaWalker vecBuilder(
		[&](RootNode* b)
		{ 
			for (auto& child : b->children)
			{
				refs.push_back(child.get());
			}
		},
		[&](BranchNode* b)
		{ 
			for (auto& child : b->children)
			{
				refs.push_back(child.get());
			}
		},
		[](LeafNode*){}
	);

	vecBuilder.visit(_root.get());

	return refs;
}