#pragma once
#include <tile/types.h>

class IBlitter
{
public:
	virtual grid* get_tram() = 0;
};