#pragma once
#include "IComponent.h"

class CPhysics : public IComponent
{
public:
	static const CID ID = CID::Physics;

	CPhysics() {}
};

