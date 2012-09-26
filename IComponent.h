#pragma once
#include <string>

class IComponent
{
public:
	virtual ~IComponent() {}
	virtual std::string Name() = 0;
};

