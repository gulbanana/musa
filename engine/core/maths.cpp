#define _USE_MATH_DEFINES
#include <cmath>
#include "maths.h"
using namespace std;

static const Vec3<coord> maths::origin = Vec3<coord>((coord)0, (coord)0, (coord)0);

static const Vec3<degrees> maths::forward_rotation = Vec3<degrees>((degrees)0, (degrees)0, (degrees)0);	//360
static const Vec3<degrees> maths::up_rotation = Vec3<degrees>((degrees)0, (degrees)-90, (degrees)0);	
static const Vec3<degrees> maths::backward_rotation = Vec3<degrees>((degrees)0, (degrees)180, (degrees)0);

radians maths::deg2rad(const degrees d)
{
	return (radians)d * (radians)M_PI / (radians)180;
}

coord maths::aspect_ratio(int width, int height)
{
	return (coord)width / (coord)height;
}

Vec3<degrees> maths::rotation_from(Vec3<coord> from, Vec3<coord> to)
{
	auto angle = [](coord x1, coord y1, coord x2, coord y2)
	{
		auto dx = x2 - x1;
		auto dy = y2 - y1;
		auto rad = atan2(dy, dx);
		return (degrees)(rad * 180/M_PI);
	};

	degrees zangle = angle(from.x, from.y, to.x, to.y);
	degrees xangle = angle(from.y, from.z, to.y, to.z);
	degrees yangle = angle(from.z, from.x, to.z, to.x);

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