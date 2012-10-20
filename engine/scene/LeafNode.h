#pragma once
#include "IGraphNode.h"

class LeafNode : public IGraphNode
{
public:
	LeafNode(std::shared_ptr<IEntity>);
	virtual void accept(IGraphWalker* visitor) override;
};

