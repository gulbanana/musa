#include <engine/core.h>
#include <cmath>
#include <functional>
#include "maths.h"
using namespace std;

const point maths::origin = point((coord)0, (coord)0, (coord)0);

const angles maths::forward_rotation = angles((degrees)0, (degrees)0, (degrees)0);	//360
const angles maths::up_rotation = angles((degrees)0, (degrees)-90, (degrees)0);
const angles maths::backward_rotation = angles((degrees)0, (degrees)180, (degrees)0);

coord maths::aspect_ratio(int width, int height)
{
	return (coord)width / (coord)height;
}

angles maths::rotation_from(point from, point to)
{
	auto angle = [&](function<coord(point)> a1, function<coord(point)> a2)
	{
		auto d1 = a1(to) - a1(from);
		auto d2 = a2(to) - a2(from);
		return glm::degrees(atan2(d2, d1));
	};

	auto x = [](point c){return c.x;};
	auto y = [](point c){return c.y;};
	auto z = [](point c){return c.z;};

	degrees xangle = angle(y, z);
	degrees yangle = angle(z, x);
	degrees zangle = angle(x, y);

	return angles(xangle, yangle, zangle);
}

box6 maths::vertical_perspective(degrees vFOV, coord aspectRatio, coord zNear, coord zFar)
{
	auto clipHeightTangent = (coord)tan(glm::radians(vFOV / 2));

	auto height = zNear * clipHeightTangent;// / (coord)2;
	auto width = height * aspectRatio;

	auto clipLeft = -width;
	auto clipRight = width;
	auto clipBottom = -height;
	auto clipTop = height;

	return box6(clipLeft, clipBottom, zFar, clipRight, clipTop, zNear);
}

box6 maths::horizontal_perspective(degrees hFOV, coord aspectRatio, coord zNear, coord zFar)
{
	auto clipWidthTangent = (coord)tan(glm::radians(hFOV / 2));

	auto width = zNear * clipWidthTangent; // / (coord)2;	
	auto height = width / aspectRatio;			

	auto clipLeft = -width;
	auto clipRight = width;
	auto clipBottom = -height;
	auto clipTop = height;

	return box6(clipLeft, clipBottom, zFar, clipRight, clipTop, zNear);
}

point maths::midpoint(point x, point y)
{
	return (x + y) / (coord)2.0;
}

angles maths::vmod(angles v, degrees d)
{
	return angles(fmod(v.x,d), fmod(v.y,d), fmod(v.z,d));
}