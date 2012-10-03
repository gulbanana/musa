#pragma once
#include "Vec3.h"

template<typename T>
struct Box6
{
	T x1, y1, z1, x2, y2, z2;

#pragma region accessors
	T left() { return x1; }
	T bottom() { return y1; }
	T front() { return z1; }
	T right() { return x2; }
	T top() { return y2; }
	T back() { return z2; }

	Vec3<T> bottomLeftBack() { return Vec3<T>(x1,y1,z1); }
	Vec3<T> topRightFront() { return Vec3<T>(x2,y2,z2); }
	Vec3<T> origin() { return bottomLeftBack(); }

	T width() { return x2-x1; }
	T height() { return y2-y1; }
	T depth() { return z2-z1; }
#pragma endregion

#pragma region constructors
	Box6(T left, T bottom, T back, T right, T top, T front) : 
		x1(left), y1(bottom), z1(back), x2(right), y2(top), z2(front) {}
	Box6(Vec3<T> bottomLeftBack, Vec3<T> topRightFront) : 
		x1(bottomLeftBack.x), 
		y1(bottomLeftBack.y), 
		z1(bottomLeftBack.z), 
		x2(topRightFront.x), 
		y2(topRightFront.y),
		z2(topRightFront.z) {}
	Box6(Vec3<T> origin, T width, T height, T depth) : 
		x1(origin.x), y1(origin.y), z1(origin.z), x2(origin.x + width), y2(origin.y + height), z2(origin.z + depth) {}
#pragma endregion

#pragma region arithmetic
	Box6 operator+(Vec3<T> const& p) const { return Box6(x1 + p.x, y1 + p.y, z1 + p.z, x2 + p.x, y2 + p.y, z2 + p.z); }
	Box6 operator-(Vec3<T> const& p) const { return Box6(x1 - p.x, y1 - p.y, z1 - p.z, x2 - p.x, y2 - p.y, z2 - p.z); }
#pragma endregion
};
