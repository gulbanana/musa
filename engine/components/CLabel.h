#pragma once

class CLabel : public Identified<IComponent, CMP::Label>
{
public:
	std::string text;
	CLabel(std::string t) : text(t) {}
};

