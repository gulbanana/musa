#pragma once
#include "IGraphNode.h"

class BranchNode : public IGraphNode
{
public:
	std::shared_ptr<IEntity> entity;
	std::vector<std::unique_ptr<IGraphNode>> children;

	BranchNode(std::shared_ptr<IEntity> e) : entity(e) {}
	virtual void accept(IGraphWalker* visitor) override { visitor->visit(this); }
};

