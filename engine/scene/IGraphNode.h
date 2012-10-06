#pragma once
#include <engine/core.h>
#include "IGraphWalker.h"

class IGraphNode : public IEntity
{
public:
	virtual ~IGraphNode() = 0;
	virtual void accept(IGraphWalker* visitor) = 0;
};