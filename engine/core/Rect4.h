#pragma once
#include <algorithm>
#include "Vec2.h"
#include "Box6.h"

template <typename T>
struct Rect4
{
	T x1, y1, x2, y2;

	//accessors - interface with the rect any way you like
	T left() const		{ return x1; }
	T bottom() const	{ return y1; }
	T right() const		{ return x2; }
	T top() const		{ return y2; }
	Vec2<T> bottomLeft() const { return Vec2<T>(x1,y1); }
	Vec2<T> topRight() const	{ return Vec2<T>(x2,y2); }
	Vec2<T> origin() const		{ return bottomLeft(); }
	T width() const		{ return x2-x1; }
	T height() const	{ return y2-y1; }

	///constructors
	Rect4(T left, T bottom, T right, T top) : x1(left), y1(bottom), x2(right), y2(top) {}
	Rect4(Vec2<T> bottomLeft, Vec2<T> topRight) : x1(bottomLeft.x), y1(bottomLeft.y), x2(topRight.x), y2(topRight.y) {}
	Rect4(Vec2<T> origin, T width, T height) : x1(origin.x), y1(origin.y), x2(origin.x + width), y2(origin.y + height) {}
	explicit Rect4(Box6<T> box) : x1(box.x1), y1(box.y1), x2(box.x2), y2(box.y2) {}

#pragma region arithmetic
	Rect4 operator+(Vec2<T> const& p) const { return Rect4<T>(x1 + p.x, y1 + p.y, x2 + p.x, y2 + p.y); }
	Rect4 operator-(Vec2<T> const& p) const { return Rect4<T>(x1 - p.x, y1 - p.y, x2 - p.x, y2 - p.y); }
#pragma endregion
	
#pragma region utility
	bool contains(T x, T y) const { return (x >= x1) && (x < x2) && (y >= y1) && (y < y2); }
	bool contains(Vec2<T> const& point) const { return contains(point.x, point.y); }
	bool intersects(Rect4 const& rectangle) const
	{
		Rect4 intersection((coord)0,(coord)0,(coord)0,(coord)0);
		return intersects(rectangle, intersection);
	}
	bool intersects(Rect4 const& rectangle, Rect4& intersection) const
	{
		auto interLeft = std::max(x1, rectangle.x1);
		auto interBottom = std::max(y1, rectangle.y1);
		auto interRight = std::min(x2, rectangle.x2);
		auto interTop = std::min(y2, rectangle.y2);

		// If the intersection is valid (positive non zero area), then there is an intersection
		if ((interLeft < interRight) && (interBottom < interTop))
		{
			intersection = Rect4(interLeft, interBottom, interRight, interTop);
			return true;
		}
		else
		{
			intersection = Rect4((coord)0, (coord)0, (coord)0, (coord)0);
			return false;
		}
	}
	Rect4 max(Rect4 const& a, Rect4 const& b) 
	{ 
		return Rect4(std::max(a.x1,b.x1), std::max(a.y1,b.y1), std::max(a.x2,b.x2), std::max(a.y2,b.y2)); 
	}
#pragma endregion

#pragma region conversions
	operator Box6<T>()
	{
		return Box6<T>(x1, y1, 0.f, x2, y2, 0.f);
	}
#pragma endregion
};