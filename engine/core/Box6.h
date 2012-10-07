#pragma once
#include <string>
#include "Vec3.h"

template<typename T>
struct Box6
{
	T x1, y1, z1, x2, y2, z2;

#pragma region accessors
	T left() const   { return x1; }
	T bottom() const { return y1; }
	T back() const  { return z1; }
	T right() const  { return x2; }
	T top() const    { return y2; }
	T front() const   { return z2; }

	Vec3<T> bottomLeftBack() const { return Vec3<T>(x1,y1,z1); }
	Vec3<T> topRightFront() const  { return Vec3<T>(x2,y2,z2); }
	Vec3<T> origin() const         { return bottomLeftBack(); }

	T width() const  { return x2-x1; }
	T height() const { return y2-y1; }
	T depth() const  { return z2-z1; }
#pragma endregion

#pragma region constructors
	template<typename U>
	Box6(U left, U bottom, U back, U right, U top, U front) : 
		x1((T)left), y1((T)bottom), z1((T)back), x2((T)right), y2((T)top), z2((T)front) {}
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

#pragma region utility
	bool intersects(Box6 const& prism) const
	{
		Box6 intersection((T)0,(T)0,(T)0,(T)0,(T)0,(T)0);
		return intersects(prism, intersection);
	}

	bool intersects(Box6 const& prism, Box6& intersection) const
	{
		auto interLeft = std::max(x1, prism.x1);
		auto interBottom = std::max(y1, prism.y1);
		auto interBack = std::max(z1, prism.z1);
		auto interRight = std::min(x2, prism.x2);
		auto interTop = std::min(y2, prism.y2);
		auto interFront = std::min(z2, prism.z2);

		// If the intersection is valid (positive non zero area), then there is an intersection
		if ((interLeft < interRight) && (interBottom < interTop) && (interBack < interFront))
		{
			intersection = Box6(interLeft, interBottom, interBack, interRight, interTop, interFront);
			return true;
		}
		else
		{
			intersection = Box6((T)0,(T)0,(T)0,(T)0,(T)0,(T)0);
			return false;
		}
	}
#pragma endregion
};

template<typename T>
std::string to_string(Box6<T> box)
{
	return std::string("{") +
    std::to_string(box.x1) + "," +
	std::to_string(box.y1) + "," +
	std::to_string(box.z1) + "},{" +
	std::to_string(box.x2) + "," +
	std::to_string(box.y2) + "," +
    std::to_string(box.z2) + "}";
}