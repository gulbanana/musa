#pragma once
#include <string>
#include "IComponent.h"

class CLabel : public IComponent
{
	IDENTIFIED(IComponent, Label);
	std::string text;
	CLabel(std::string t) : text(t) {}
};

