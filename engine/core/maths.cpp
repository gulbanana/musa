#include <engine/core.h>
#include <cmath>
#include <functional>
#include "maths.h"
using namespace std;

const Vec3<coord> maths::origin = Vec3<coord>((coord)0, (coord)0, (coord)0);

const Vec3<degrees> maths::forward_rotation = Vec3<degrees>((degrees)0, (degrees)0, (degrees)0);	//360
const Vec3<degrees> maths::up_rotation = Vec3<degrees>((degrees)0, (degrees)-90, (degrees)0);
const Vec3<degrees> maths::backward_rotation = Vec3<degrees>((degrees)0, (degrees)180, (degrees)0);

radians maths::deg2rad(const degrees d)
{
	return (radians)d * (radians)M_PI / (radians)180;
}

degrees maths::rad2deg(const radians r)
{
	return (degrees)r * (degrees)180 / (degrees)M_PI;
}

coord maths::aspect_ratio(int width, int height)
{
	return (coord)width / (coord)height;
}

Vec3<degrees> maths::rotation_from(Vec3<coord> from, Vec3<coord> to)
{
	auto angle = [&](function<coord(Vec3<coord>)> a1, function<coord(Vec3<coord>)> a2)
	{
		auto d1 = a1(to) - a1(from);
		auto d2 = a2(to) - a2(from);
		return rad2deg((radians)atan2(d2, d1));
	};

	auto x = [](Vec3<coord> c){return c.x;};
	auto y = [](Vec3<coord> c){return c.y;};
	auto z = [](Vec3<coord> c){return c.z;};

	degrees xangle = angle(y, z);
	degrees yangle = angle(z, x);
	degrees zangle = angle(x, y);

	return Vec3<degrees>(xangle, yangle, zangle);
}

Box6<coord> maths::vertical_perspective(degrees vFOV, coord aspectRatio, coord zNear, coord zFar)
{
	auto clipHeightTangent = (coord)tan(deg2rad(vFOV / (degrees)2));

	auto height = zNear * clipHeightTangent;// / (coord)2;
	auto width = height * aspectRatio;

	auto clipLeft = -width;
	auto clipRight = width;
	auto clipBottom = -height;
	auto clipTop = height;

	return Box6<coord>(clipLeft, clipBottom, zFar, clipRight, clipTop, zNear);
}

Box6<coord> maths::horizontal_perspective(degrees hFOV, coord aspectRatio, coord zNear, coord zFar)
{
	auto clipWidthTangent = (coord)tan(deg2rad(hFOV / (degrees)2));

	auto width = zNear * clipWidthTangent; // / (coord)2;	
	auto height = width / aspectRatio;			

	auto clipLeft = -width;
	auto clipRight = width;
	auto clipBottom = -height;
	auto clipTop = height;

	return Box6<coord>(clipLeft, clipBottom, zFar, clipRight, clipTop, zNear);
}
