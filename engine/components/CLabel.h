#pragma once
#include <string>
#include <engine/core.h>

class CLabel : public Identified<IComponent, CMP::Label>
{
public:
	std::string text;
	CLabel(std::string t) : text(t) {}
};

