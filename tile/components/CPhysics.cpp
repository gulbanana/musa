#include <tile/stdafx.h>
#include "CPhysics.h"

namespace std
{
	string to_string(CPhysics p)
	{
		return string("Physics{") 
			+ "solid: " + to_string(p.solid) + ","
			+ "can_collide: " + to_string(p.can_collide) 
		+ "}";
	}
}