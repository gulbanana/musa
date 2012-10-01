#pragma once
#include "IBounder.h"

template<typename TBounds>
class IBounded
{
public:
	virtual ~IBounded() {}
	virtual TBounds accept(IBounder<TBounds>* boundsCalculator) = 0;
};