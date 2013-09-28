#pragma once
#include <core/framework.h>
#include "IGraphNode.h"

class LeafNode : public IGraphNode
{
public:
	std::shared_ptr<IEntity> entity;

	LeafNode(std::shared_ptr<IEntity> e) : entity(e) {}
	virtual void accept(IGraphWalker* visitor) override { visitor->visit(this); }
};

