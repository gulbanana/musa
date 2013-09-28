#pragma once
#include <mesh/types.h>

class CInput : public Identified<IComponent, CMP::Input>
{
public:
	coord speed;
	
	CInput(coord speed) : speed(speed) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CInput(*this)); }
};

