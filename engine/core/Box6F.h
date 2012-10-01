#pragma once
#include "Vector3F.h"

class Box6F
{
	float x1, y1, z1, x2, y2, z2;

public:
	float left() { return x1; }
	float bottom() { return y1; }
	float front() { return z1; }
	float right() { return x2; }
	float top() { return y2; }
	float back() { return z2; }

	Vector3F bottomLeftBack() { return Vector3F(x1,y1,z1); }
	Vector3F topRightFront() { return Vector3F(x2,y2,z2); }
	Vector3F origin() { return bottomLeftBack(); }

	float width() { return x2-x1; }
	float height() { return y2-y1; }
	float depth() { return z2-z1; }

	Box6F(float left, float bottom, float back, float right, float top, float front) : 
		x1(left), y1(bottom), z1(back), x2(right), y2(top), z2(front) {}
	Box6F(Vector3F bottomLeftBack, Vector3F topRightFront) : 
		x1(bottomLeftBack.x), 
		y1(bottomLeftBack.y), 
		z1(bottomLeftBack.z), 
		x2(topRightFront.x), 
		y2(topRightFront.y),
		z2(topRightFront.z) {}
	Box6F(Vector3F origin, float width, float height, float depth) : 
		x1(origin.x), y1(origin.y), z1(origin.z), x2(origin.x + width), y2(origin.y + height), z2(origin.z + depth) {}
};
