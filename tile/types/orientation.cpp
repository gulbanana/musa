#include <tile/stdafx.h>
#include "orientation.h"

namespace std
{
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