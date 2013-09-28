#pragma once
#include "IGraphWalker.h"

class IGraphNode
{
public:
	virtual ~IGraphNode() {}
	virtual void accept(IGraphWalker* visitor) = 0;
};