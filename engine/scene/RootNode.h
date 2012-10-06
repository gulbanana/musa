#pragma once
#include "BranchNode.h"

//root of a scene graph - trees descended from this node should always be valid
//todo: add a mutex
class RootNode : public BranchNode
{
public:
	RootNode(); 
	~RootNode();

	virtual void accept(IGraphWalker* visitor);
};

