#pragma once

class CInput : public Identified<IComponent, CMP::Input>
{
public:
	dist speed;
	angle direction;
	
	CInput(dist speed, angle direction) : speed(speed), direction(direction) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CInput(*this)); }
};

