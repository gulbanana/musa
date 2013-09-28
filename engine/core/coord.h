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
*/

struct coord
{
	const int x;
	const int y;
	const int z;

	coord(int _x, int _y) : x(_x), y(_y), z(0) {}
	coord(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

	bool above(coord& c) const { return z > c.z; }

	coord operator+(coord const& c) const { return coord(x + c.x, y + c.y, z + c.z); }
	coord operator-(coord const& c) const { return coord(x - c.x, y - c.y, z - c.z); }

	bool operator==(coord const& c) const { return x == c.x && y == c.y && z == c.z; }
};