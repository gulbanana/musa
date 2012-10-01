#pragma once
#include <string>
#include <engine/core.h>

class CLabel : public Identified<IComponent, CID::Label>
{
public:
	std::string text;
	CLabel(std::string t) : text(t) {}
};

