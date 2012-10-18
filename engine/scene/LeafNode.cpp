#include <engine/core.h>
#include "LeafNode.h"

void LeafNode::accept(IGraphWalker* visitor)
{ 
	visitor->visit(this); 
}