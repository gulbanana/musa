#include <engine/core.h>
#include "BranchNode.h"

void BranchNode::accept(IGraphWalker* visitor)
{ 
	visitor->visit(this); 
}