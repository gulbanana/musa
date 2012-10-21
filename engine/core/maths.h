#pragma once
#include "typedefs.h"

namespace maths
{
    extern const point origin;

	extern const lnseg x_axis;
	extern const lnseg y_axis;
	extern const lnseg z_axis;

	extern const angle left_rotation;
	extern const angle right_rotation;
	extern const angle up_rotation;
	extern const angle down_rotation;
	extern const angle forward_rotation;
	extern const angle backward_rotation;

	lnseg rot2vec(angle direction);
	angle vec2rot(lnseg direction);
	angle rotation_between(point from, point to);

	coord aspect_ratio(int width, int height);

	box6 vertical_perspective(degrees vFOV, coord aspectRatio, coord front, coord back);
	box6 horizontal_perspective(degrees hFOV, coord aspectRatio, coord front, coord back);

	point midpoint(point x, point y);

	eulers vmod(eulers v, degrees d);
}