#pragma once
#include "IGraphNode.h"

class BranchNode : public IGraphNode
{
public:
	BranchNode(std::shared_ptr<IEntity>);
	virtual ~BranchNode() {}

	virtual void accept(IGraphWalker* visitor);
	std::vector<std::shared_ptr<IGraphNode>> children;
};

