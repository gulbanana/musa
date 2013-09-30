#pragma once
#include <core/framework.h>
#include <tile/types.h>

class CDraw : public Identified<CDraw, IComponent>
{
public:
    tile layout;

	//constructors
    CDraw(tile t) : layout(t) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CDraw(*this)); }
};

namespace std
{
	string to_string(CDraw d);
}