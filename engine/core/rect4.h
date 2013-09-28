#pragma once
#include <algorithm>
#include "box6.h"

struct rect4
{
	coord x1, y1, x2, y2;

	//accessors - interface with the rect any way you like
	coord left() const		 { return x1; }
	coord bottom() const	 { return y1; }
	coord right() const		 { return x2; }
	coord top() const		 { return y2; }
	point bottomLeft() const { return point(x1,y1); }
	point topRight() const	 { return point(x2,y2); }
	point origin() const	 { return bottomLeft(); }
	coord width() const		 { return x2-x1; }
	coord height() const	 { return y2-y1; }

	///constructors
	rect4(coord left, coord bottom, coord right, coord top) : x1(left), y1(bottom), x2(right), y2(top) {}
	rect4(point bottomLeft, point topRight) : x1(bottomLeft.x), y1(bottomLeft.y), x2(topRight.x), y2(topRight.y) {}
	rect4(point origin, coord width, coord height) : x1(origin.x), y1(origin.y), x2(origin.x + width), y2(origin.y + height) {}
	explicit rect4(box6 box) : x1(box.x1), y1(box.y1), x2(box.x2), y2(box.y2) {}

#pragma region arithmetic
	rect4 operator+(point const& p) const { return rect4(x1 + (coord)p.x, y1 + (coord)p.y, x2 + (coord)p.x, y2 + (coord)p.y); }
	rect4 operator-(point const& p) const { return rect4(x1 - (coord)p.x, y1 - (coord)p.y, x2 - (coord)p.x, y2 - (coord)p.y); }
#pragma endregion
	
#pragma region utility
	bool contains(coord x, coord y) const { return (x >= x1) && (x < x2) && (y >= y1) && (y < y2); }
	bool contains(point const& p) const { return contains((coord)p.x, (coord)p.y); }
	bool intersects(rect4 const& rectangle) const
	{
		rect4 intersection((coord)0,(coord)0,(coord)0,(coord)0);
		return intersects(rectangle, intersection);
	}
	bool intersects(rect4 const& rectangle, rect4& intersection) const
	{
		auto interLeft = std::max(x1, rectangle.x1);
		auto interBottom = std::max(y1, rectangle.y1);
		auto interRight = std::min(x2, rectangle.x2);
		auto interTop = std::min(y2, rectangle.y2);

		// If the intersection is valid (positive non zero area), then there is an intersection
		if ((interLeft < interRight) && (interBottom < interTop))
		{
			intersection = rect4(interLeft, interBottom, interRight, interTop);
			return true;
		}
		else
		{
			intersection = rect4((coord)0, (coord)0, (coord)0, (coord)0);
			return false;
		}
	}
	rect4 max(rect4 const& a, rect4 const& b) 
	{ 
		return rect4(std::max(a.x1,b.x1), std::max(a.y1,b.y1), std::max(a.x2,b.x2), std::max(a.y2,b.y2)); 
	}
#pragma endregion

#pragma region conversions

#pragma endregion
};