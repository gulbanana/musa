#include <engine/core.h>
#include <cmath>
#include "constants.h"
using namespace std;

const colour Colour::RED =         colour(1.f, 0.f, 0.f, 1.f);
const colour Colour::GREEN =       colour(0.f, 1.f, 0.f, 1.f);
const colour Colour::BLUE =        colour(0.f, 0.f, 1.f, 1.f);
const colour Colour::CYAN =        colour(0, 1.f, 1.f, 1.f);
const colour Colour::MAGENTA =     colour(1.f, 0.f, 1.f, 1.f);
const colour Colour::YELLOW =      colour(1.f, 1.f, 0.f, 1.f);
const colour Colour::BLACK =       colour(0.f, 0.f, 0.f, 1.f);
const colour Colour::WHITE =       colour(1.f, 1.f, 1.f, 1.f);
const colour Colour::TRANSLUCENT = colour(0.f, 0.0, 0.f, 0.f);

const point constants::origin(0, 0, 0);

const lnseg constants::x_axis(1, 0, 0);
const lnseg constants::y_axis(0, 1, 0);
const lnseg constants::z_axis(0, 0, 1);

const rotation constants::forward_orientation(constants::identity_rotation);
const rotation constants::backward_orientation(0, 0, 1, 0);
const rotation constants::left_orientation(eulers(0, -90, 0));
const rotation constants::right_orientation(eulers(0, 90, 0));
const rotation constants::up_orientation(eulers(-90, 0, 0));
const rotation constants::down_orientation(eulers(90, 0, 0));

const rotation constants::identity_rotation(1, 0, 0, 0);

rotation constants::rotation_between(point from, point to)
{
	auto direction = glm::normalize(to - from);
	return vec2rot(direction);
}

rotation constants::vec2rot(lnseg front)
{
	//calculate normals
	auto right = glm::cross(y_axis, front);
	auto up = glm::cross(front, right);

	//create a unit quaternion
	rotation result;

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

box6 constants::vertical_perspective(degrees vFOV, coord aspectRatio, coord zNear, coord zFar)
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

box6 constants::horizontal_perspective(degrees hFOV, coord aspectRatio, coord zNear, coord zFar)
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

point constants::midpoint(point x, point y)
{
	return (x + y) / (coord)2.0;
}

eulers constants::vmod(eulers v, degrees d)
{
	return eulers(fmod(v.x,d), fmod(v.y,d), fmod(v.z,d));
}