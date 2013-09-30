#include <tile/stdafx.h>
#include "orientation.h"
#include "vec2.h"
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

namespace std 
{
	string to_string(vec2 v)
	{
		return string("[") 
			+ to_string(v.x) + ","
			+ to_string(v.y) 
		+ "]";
	}
}