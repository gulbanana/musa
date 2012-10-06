#pragma once
#include "IGraphNode.h"

class LeafNode : public IGraphNode
{
public:
	virtual void accept(IGraphWalker* visitor) override;
};

