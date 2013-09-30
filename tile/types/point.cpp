#include <tile/stdafx.h>
#include "point.h"

bool point::operator==(point const& c) const
{
    return x == c.x && y == c.y && z == c.z;
}

bool point::operator!=(point const& c) const
{
    return x != c.x || y == c.y || z == c.z;
}

point point::operator+(point const& c) const
{
    return point(x + c.x, y + c.y, z + c.z);
}

point point::operator-(point const& c) const
{
    return point(x - c.x, y - c.y, z - c.z);
}

point point::operator+(vec2 const& v) const
{
    auto xRaw = (dist)x + dx + v.x;
    auto yRaw = (dist)y + dy + v.y;
    auto xFloor = roundPoint(xRaw);
    auto yFloor = roundPoint(yRaw);
    
    return point(xFloor, yFloor, z, xRaw - xFloor, yRaw - yFloor, dz);
}

point point::operator-(vec2 const& v) const
{
    auto xRaw = (dist)x + dx - v.x;
    auto yRaw = (dist)y + dy - v.y;
    auto xFloor = roundPoint(xRaw);
    auto yFloor = roundPoint(yRaw);
    
    return point(xFloor, yFloor, z, xRaw - xFloor, yRaw - yFloor, dz);
}

point point::operator+(dist modz) const
{
    auto zRaw = (dist)z + dz + modz;
    auto zFloor = roundPoint(zRaw);
    
    return point(x, y, zFloor, dx, dy, zRaw - zFloor);
}

point point::operator-(dist modz) const
{
    auto zRaw = (dist)z + dz - modz;
    auto zFloor = roundPoint(zRaw);
    
    return point(x, y, zFloor, dx, dy, zRaw - zFloor);
}

bool point::above(point& c) const
{
    return z > c.z;
}

bool point::below(point& c) const
{
    return z < c.z;
}

coord roundPoint(dist d)
{
    auto fd = (coord)d;
    
    if ((d - (dist)fd) <= 0.5)
        return fd;
    else
        return fd+1;
}

const point point::ORIGIN = point(0, 0, 0);

namespace std
{    
	string to_string(point p)
	{
		return string("(")
        + to_string(p.x) + "+" + to_string(p.dx) + ","
        + to_string(p.y) + "+" + to_string(p.dy) + ","
        + to_string(p.z) + "+" + to_string(p.dz)
		+ ")";	
	}
}