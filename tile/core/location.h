/*
WORLD SPACE
coordinate system: tile units
the world has X and Y coordinates from a hypothetical origin, as well as height Z
Z 0 is "ground level" - the location of most entities. the 'floor' is therefore mostly at level -1.
Y is "up"; X is "right"

CAMERA SPACE
coordinate system: pixels, tiles
a camera is an X1xY1 2d frame, containing X2xY2 tiles rendered as text characters. 
the main camera is either contained within a window, or fullscreen
world space is *projected* to camera space according to its font, aspect ratio, font
every time the camera needs to be reset, resize() is sent to the renderer
when it *moves* this does not happen however. so where is its position & orientation kept? can it be an entity with a CPosition?

OBJECT SPACE
coordinate system: tile units
every entity has its own relative coordinates and an origin in the centre. 
these are fixed, or rather they change only if the entity's state changes
entities may have 'sprite-sheet' rotations and animation, or automatic transformations in cardinal directions
initially they'll only have X and Y, but will be *located* along Z
the entity is projected from "modelobject" space to "world" space in order to display it

COORDINATES AND DISTANCES
locations are always a fixed tile index, to simplify many other subsystems. movement is fractional. 
this means that vectors have to be accumulated until they result in an actual change of position.
*/
#pragma once

typedef int coord;
typedef float dist;

struct vec2
{
	const dist x;
	const dist y;

	vec2(dist _x, dist _y) : x(_x), y(_y) {}

	bool operator==(vec2 const& v) const { return x == v.x && y == v.y; }
	bool operator!=(vec2 const& v) const { return x != v.x || y == v.y; }

	vec2 operator+(vec2 const& v) const { return vec2(x + v.x, y + v.y); }
	vec2 operator-(vec2 const& v) const { return vec2(x - v.x, y - v.y); }
	vec2 operator*(float c) const { return vec2(x * c, y * c); }
	vec2 operator/(float c) const { return vec2(x / c, y / c); }

	angle direction();
	float magnitude();

	static const vec2 ZERO;
};

struct point
{
	const coord x;
	const coord y;
	const coord z;

	point(coord _x, coord _y) : x(_x), y(_y), z(0) {}
	point(coord _x, coord _y, coord _z) : x(_x), y(_y), z(_z) {}

	bool operator==(point const& c) const { return x == c.x && y == c.y && z == c.z; }
	bool operator!=(point const& c) const { return x != c.x || y == c.y || z == c.z; }

	point operator+(point const& c) const { return point(x + c.x, y + c.y, z + c.z); }
	point operator-(point const& c) const { return point(x - c.x, y - c.y, z - c.z); }
	point operator+(vec2 const& v) const { return point((coord)((dist)x + v.x), (coord)((dist)y + v.y), z); }
	point operator-(vec2 const& v) const { return point((coord)((dist)x - v.x), (coord)((dist)y - v.y), z); }

	bool above(point& c) const { return z > c.z; }
	bool below(point& c) const { return z < c.z; }

	static const point ORIGIN;
};

