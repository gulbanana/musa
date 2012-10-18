#pragma once
#include "typedefs.h"

namespace maths
{
    extern const point origin;

	extern const angles up_rotation;
	extern const angles forward_rotation;
	extern const angles backward_rotation;

	angles vec2rot(point direction);

	angles rotation_from(point from, point to);

	coord aspect_ratio(int width, int height);

	box6 vertical_perspective(degrees vFOV, coord aspectRatio, coord front, coord back);
	box6 horizontal_perspective(degrees hFOV, coord aspectRatio, coord front, coord back);

	point midpoint(point x, point y);

	angles vmod(angles v, degrees d);
}