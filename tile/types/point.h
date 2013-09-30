#pragma once
#include "vec2.h"

struct point
{
	coord x;
    dist dx;
	coord y;
    dist dy;
	coord z;
    dist dz;
    
	point(coord _x, coord _y) : x(_x), y(_y), z(0), dx(0), dy(0), dz(0) {}
	point(coord _x, coord _y, coord _z) : x(_x), y(_y), z(_z), dx(0), dy(0), dz(0) {}
    point(coord _x, coord _y, coord _z, dist _dx, dist _dy, dist _dz) : x(_x), y(_y), z(_z), dx(_dx), dy(_dy), dz(_dz) {}
    
	bool operator==(point const& c) const;
	bool operator!=(point const& c) const;
    
	point operator+(point const& c) const;
	point operator-(point const& c) const;
    
	point operator+(vec2 const& v) const;
	point operator-(vec2 const& v) const;
    
    point operator+(dist modz) const;
    point operator-(dist modz) const;
    
	bool above(point& c) const;
	bool below(point& c) const;
    
	static const point ORIGIN;
};

coord roundPoint(dist);

namespace std
{
	string to_string(point);
}