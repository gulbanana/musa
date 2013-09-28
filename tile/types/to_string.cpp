#include <tile/stdafx.h>
#include "location.h"
#include "orientation.h"

namespace std 
{
	string to_string(vec2 v)
	{
		return string("[") 
			+ to_string(v.x) + ","
			+ to_string(v.y) 
		+ "]";
	}

	string to_string(point p)
	{
		return string("(") 
			+ to_string(p.x) + ","
			+ to_string(p.y) + ","
			+ to_string(p.z) 
		+ ")";	
	}

	string to_string(dir d)
	{
		switch (d)
		{
		case dir::UP:
			return "up";

		case dir::DOWN:
			return "down";

		case dir::LEFT:
			return "left";

		case dir::RIGHT:
			return "right";

		default:
			return "unknown-direction";
		}
	}
}