#pragma once
#include "Vector3F.h"

class Box6F
{
	float x1, y1, z1, x2, y2, z2;

public:
	float left() { return x1; }
	float top() { return y1; }
	float front() { return z1; }
	float right() { return x2; }
	float bottom() { return y2; }
	float back() { return z2; }

	Vector3F topLeftFront() { return Vector3F(x1,y1,z1); }
	Vector3F bottomRightBack() { return Vector3F(x2,y2,z2); }
	Vector3F origin() { return topLeftFront(); }

	float width() { return x2-x1; }
	float height() { return y2-y1; }
	float depth() { return z2-z1; }

	Box6F(float left, float top, float front, float right, float bottom, float back) : 
		x1(left), y1(top), z1(front), x2(right), y2(bottom), z2(back) {}
	Box6F(Vector3F topLeftFront, Vector3F bottomRightBack) : 
		x1(topLeftFront.x), 
		y1(topLeftFront.y), 
		z1(topLeftFront.z), 
		x2(bottomRightBack.x), 
		y2(bottomRightBack.y),
		z2(bottomRightBack.z) {}
	Box6F(Vector3F origin, float width, float height, float depth) : 
		x1(origin.x), y1(origin.y), z1(origin.z), x2(origin.x + width), y2(origin.y + height), z2(origin.z + depth) {}
};
