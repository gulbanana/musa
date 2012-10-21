#include <engine/core.h>
#include <cmath>
#include <functional>
#include "maths.h"
using namespace std;

const point maths::origin(0, 0, 0);

const lnseg maths::x_axis(1, 0, 0);
const lnseg maths::y_axis(0, 1, 0);
const lnseg maths::z_axis(0, 0, 1);

const angle maths::left_rotation(1, 0, 0, 0);
const angle maths::right_rotation(0, 0, 1, 0);
const angle maths::up_rotation(1, 0, 0, 0);
const angle maths::down_rotation(0, 0, 1, 0);
const angle maths::forward_rotation(1, 0, 0, 0);
const angle maths::backward_rotation(0, 0, 1, 0);

coord maths::aspect_ratio(int width, int height)
{
	return (coord)width / (coord)height;
}

angle maths::rotation_between(point from, point to)
{
	auto direction = glm::normalize(to - from);
	return vec2rot(direction);
}

angle maths::vec2rot(lnseg front)
{
	//calculate normals
	auto right = glm::cross(y_axis, front);
	auto up = glm::cross(front, right);

	//create a unit quaternion
	angle result;

#ifdef GLM_PRECISION_HIGHP_FLOAT
	result.w = sqrt(1.0 + right.x + up.y + front.z) / 2.0;
	coord scale = result.w * 4.0;	
#else
	result.w = sqrtf(1.f + right.x + up.y + front.z) / 2.f;
	coord scale = result.w * 4.f;	
#endif

	result.x = (up.z - front.y) / scale;
	result.y = (front.x - right.z) / scale;
	result.z = (right.y - up.x) / scale;

	return result;
}

lnseg maths::rot2vec(angle rotation)
{
	return rotation * z_axis;
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

eulers maths::vmod(eulers v, degrees d)
{
	return eulers(fmod(v.x,d), fmod(v.y,d), fmod(v.z,d));
}