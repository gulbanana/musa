#include <tile/stdafx.h>
#include "CVelocity.h"

namespace std
{
	string to_string(CVelocity v)
	{
		return string("Velocity{") 
			+ "vector: " + to_string(v.vector) + ", "
			+ "versor: " + to_string(v.versor) 
		+ "}";
	}
}