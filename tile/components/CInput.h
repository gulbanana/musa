#pragma once
#include <core/framework.h>
#include <tile/types.h>

class CInput : public Identified<CInput,IComponent>
{
public:
	dist speed;
	angle direction;
	
	CInput(dist speed, angle direction) : speed(speed), direction(direction) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CInput(*this)); }
};

namespace std
{
	string to_string(CInput i)
	{
		return string("Input{") 
			+ "speed: " + to_string(i.speed) + ","
			+ "direction: " + to_string(i.direction) 
		+ "}";
	}
}