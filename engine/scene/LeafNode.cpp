#include <engine/core.h>
#include "LeafNode.h"
using namespace std;

LeafNode::LeafNode(shared_ptr<IEntity> entity)
{
	_entity = entity;
}

void LeafNode::accept(IGraphWalker* visitor)
{ 
	visitor->visit(this); 
}