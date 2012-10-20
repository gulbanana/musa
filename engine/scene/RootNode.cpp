#include <engine/core.h>
#include <engine/components.h>
#include "RootNode.h"
using namespace std;

RootNode::RootNode(shared_ptr<IEntity> entity) : BranchNode(entity)
{ 
	_entity->add_component(make_unique<CScene>());
}

RootNode::~RootNode()
{
}

void RootNode::accept(IGraphWalker* visitor)
{ 
	visitor->visit(this); 
}