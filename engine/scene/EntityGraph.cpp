#include <vector>
#include <algorithm>
#include "EntityGraph.h"
#include "LambdaWalker.h"
using namespace std;

//todo: constructors which load a level from structured data!
EntityGraph::EntityGraph() : _root(make_shared<RootNode>()) {}

void EntityGraph::add_entity(shared_ptr<IGraphNode> entity)
{
	_root->children.push_back(entity);
}

RootNode* EntityGraph::entity_tree()
{
	return _root.get();
}

vector<shared_ptr<IEntity>> EntityGraph::entity_list()
{
	vector<shared_ptr<IEntity>> refs;
	refs.push_back(_root);

	LambdaWalker vecBuilder(
		[](LeafNode*){}, 
		[&](BranchNode* b){ refs.insert(refs.end(), b->children.begin(), b->children.end()); }
	);

	vecBuilder.visit(_root.get());

	return refs;
}