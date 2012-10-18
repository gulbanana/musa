#pragma once

class CPlayer : public Identified<IComponent, CMP::Player>
{
public:
	coord speed;
	
	CPlayer(coord speed) : speed(speed) {}
};

