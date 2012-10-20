#include <engine/core.h>
#include "BranchNode.h"
using namespace std;

BranchNode::BranchNode(shared_ptr<IEntity> entity)
{
	_entity = entity;
}

void BranchNode::accept(IGraphWalker* visitor)
{ 
	visitor->visit(this); 
}