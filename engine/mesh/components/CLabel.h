#pragma once

class CLabel : public Identified<IComponent, CMP::Label>
{
public:
	std::string text;

	CLabel(std::string t) : text(t) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CLabel(*this)); }
};

