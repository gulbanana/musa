#pragma once
#include <core/framework.h>

class CLabel : public Identified<IComponent, CMP::Label>
{
public:
	std::string text;

	CLabel(std::string t) : text(t) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CLabel(*this)); }
};

namespace std
{
	string to_string(CLabel l)
	{
		return string("Label{") 
			+ "text: " + l.text 
		+ "}";
	}
}