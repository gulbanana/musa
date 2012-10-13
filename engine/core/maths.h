#pragma once
#include "typedefs.h"
#include "Vec3.h"
#include "Box6.h"

namespace maths
{
    extern const Vec3<coord> origin;

	extern const Vec3<degrees> up_rotation;
	extern const Vec3<degrees> forward_rotation;
	extern const Vec3<degrees> backward_rotation;

	radians deg2rad(const degrees d);
	degrees rad2deg(const radians r);

	Vec3<degrees> vec2rot(Vec3<coord> direction);

	Vec3<degrees> rotation_from(Vec3<coord> from, Vec3<coord> to);

	coord aspect_ratio(int width, int height);

	Box6<coord> vertical_perspective(degrees vFOV, coord aspectRatio, coord front, coord back);
	Box6<coord> horizontal_perspective(degrees hFOV, coord aspectRatio, coord front, coord back);
}