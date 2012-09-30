#pragma once
#include "../core.h"

enum class CID
{
    Collision,
    Label,
    Physics,
    Position2D,
    Geometry2D,
    Velocity2D
};

class IComponent : public Identifiable<CID>
{
public:
	~IComponent() {}
};