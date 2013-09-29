#include <tile/stdafx.h>
#include "orientation.h"
#include "location.h"
#include <cmath>
#include <cstdlib>

angle vec2::direction()
{
	return atan2f(y, x) * 180.f / (float)M_PI;
}

dist vec2::magnitude()
{
	return abs(sqrt(x*x + y*y));
}

const vec2 vec2::ZERO = vec2(0, 0);

const point point::ORIGIN = point(0, 0, 0);