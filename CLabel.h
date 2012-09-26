#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>

class CLabel : public IComponent
{
public:
	std::string text;

	CLabel(std::string t) : text(t) {}
	std::string Name() { return "Label"; }
};

