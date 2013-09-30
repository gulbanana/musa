#include <tile/stdafx.h>
#include "orientation.h"
#include "location.h"
#include <cmath>
#include <cstdlib>

angle vec2::direction() const
{
	return atan2f(y, x) * 180.f / (float)M_PI;
}

dist vec2::magnitude() const
{
	return abs(sqrt(x*x + y*y));
}

vec2 vec2::normalise() const
{
    auto w = magnitude();
    if (abs(w) < 0.01f) return vec2(x, y);
    return vec2(x/w, y/w);
}

const vec2 vec2::ZERO = vec2(0, 0);

const point point::ORIGIN = point(0, 0, 0);

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
}