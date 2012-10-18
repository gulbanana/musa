#pragma once
#include <string>

struct box6
{
	coord x1, y1, z1, x2, y2, z2;

#pragma region accessors
	coord left() const   { return x1; }
	coord bottom() const { return y1; }
	coord back() const   { return z1; }
	coord right() const  { return x2; }
	coord top() const    { return y2; }
	coord front() const  { return z2; }

	point bottomLeftBack() const { return point(x1,y1,z1); }
	point topRightFront() const  { return point(x2,y2,z2); }
	point origin() const         { return bottomLeftBack(); }

	coord width() const  { return x2-x1; }
	coord height() const { return y2-y1; }
	coord depth() const  { return z2-z1; }
#pragma endregion

#pragma region constructors
	box6(coord left, coord bottom, coord back, coord right, coord top, coord front) : x1(left), y1(bottom), z1(back), x2(right), y2(top), z2(front) {}
	box6(point bottomLeftBack, point topRightFront) : x1(bottomLeftBack.x), y1(bottomLeftBack.y), z1(bottomLeftBack.z), x2(topRightFront.x), y2(topRightFront.y), z2(topRightFront.z) {}
	box6(point origin, coord width, coord height, coord depth) : x1(origin.x), y1(origin.y), z1(origin.z), x2(origin.x + width), y2(origin.y + height), z2(origin.z + depth) {}
#pragma endregion

#pragma region arithmetic
	box6 operator+(point const& p) const { return box6(x1 + (coord)p.x, y1 + (coord)p.y, z1 + (coord)p.z, x2 + (coord)p.x, y2 + (coord)p.y, z2 + (coord)p.z); }
	box6 operator-(point const& p) const { return box6(x1 - (coord)p.x, y1 - (coord)p.y, z1 - (coord)p.z, x2 - (coord)p.x, y2 - (coord)p.y, z2 - (coord)p.z); }
#pragma endregion

#pragma region utility
	bool intersects(box6 const& prism) const;
	bool intersects(box6 const& prism, box6& intersection) const;
#pragma endregion
};

std::string to_string(box6 box);