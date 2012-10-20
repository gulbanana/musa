#pragma once
#include "IGraphWalker.h"

class IGraphNode
{
public:
	std::shared_ptr<IEntity> _entity;
	virtual ~IGraphNode() = 0;
	virtual void accept(IGraphWalker* visitor) = 0;
};