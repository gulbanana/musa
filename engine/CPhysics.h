#pragma once
#include "IComponent.h"

class CPhysics : public IComponent
{
public:
	static const ID ID = ID::Physics;

	CPhysics() {}
};

