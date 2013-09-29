/*
Rotation is an absolute system. North/upward is the default orientation;
shapes can be transformed into 4 cardinal directions or hand-sprited to eight.

Movement, on the other hand, is precise; things can travel or fire in 
fractional directions. So facing is represented logically as a float, 
and visually as an enumeration.

Angle convention: degrees; 0 is up; 90 is right, 270 is left.
*/
#pragma once

typedef float angle;

//For convenience, the enumeration members have equivalent angles -
//a dir must still be explicitly typecast to an angle to use it
enum class dir
{
	UP        = 0,
	UPRIGHT   = 45,
	RIGHT     = 90,
	DOWNRIGHT = 135,
	DOWN      = 180,
	DOWNLEFT  = 225,
	LEFT      = 270,
	UPLEFT    = 315
};

namespace std
{
	string to_string(dir);
}
