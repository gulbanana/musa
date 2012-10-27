#pragma once
#include "typedefs.h"

namespace constants
{
    extern const point origin;

	extern const lnseg x_axis;
	extern const lnseg y_axis;
	extern const lnseg z_axis;

	extern const rotation identity_rotation;

	extern const rotation left_orientation;
	extern const rotation right_orientation;
	extern const rotation up_orientation;
	extern const rotation down_orientation;
	extern const rotation forward_orientation;
	extern const rotation backward_orientation;

	rotation vec2rot(lnseg direction);
	rotation rotation_between(point from, point to);

	box6 vertical_perspective(degrees vFOV, coord aspectRatio, coord front, coord back);
	box6 horizontal_perspective(degrees hFOV, coord aspectRatio, coord front, coord back);

	point midpoint(point x, point y);

	eulers vmod(eulers v, degrees d);
}

namespace Colour
{
	extern const colour RED;
	extern const colour GREEN;
	extern const colour BLUE;
    extern const colour CYAN;
	extern const colour MAGENTA;
	extern const colour YELLOW;
	extern const colour BLACK;
	extern const colour WHITE;
	extern const colour TRANSLUCENT;
}