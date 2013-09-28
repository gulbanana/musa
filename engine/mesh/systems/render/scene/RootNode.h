#pragma once
#include "IGraphNode.h"

class RootNode : public IGraphNode
{
public:
	std::vector<std::unique_ptr<BranchNode>> children;

	RootNode() {}
	virtual void accept(IGraphWalker* visitor) override { visitor->visit(this); }
};

