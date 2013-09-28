#include <engine/mesh/core.h>
#include "box6.h"
using namespace std;

string to_string(box6 box)
{
	return string("{") +
	    to_string(box.x1) + "," +
		to_string(box.y1) + "," +
		to_string(box.z1) + "},{" +
		to_string(box.x2) + "," +
		to_string(box.y2) + "," +
		to_string(box.z2) + "}";
}

bool box6::intersects(box6 const& prism, box6& intersection) const
{
	coord interLeft = max(x1, prism.x1);
	coord interBottom = max(y1, prism.y1);
	coord interBack = max(z1, prism.z1);
	coord interRight = min(x2, prism.x2);
	coord interTop = min(y2, prism.y2);
	coord interFront = min(z2, prism.z2);

	// If the intersection is valid (positive non zero area), then there is an intersection
	if ((interLeft < interRight) && (interBottom < interTop) && (interBack < interFront))
	{
		intersection = box6(interLeft, interBottom, interBack, interRight, interTop, interFront);
		return true;
	}
	else
	{
		intersection = box6(0, 0, 0, 0, 0, 0);
		return false;
	}
}

bool box6::intersects(box6 const& prism) const
{
	box6 intersection((coord)0,(coord)0,(coord)0,(coord)0,(coord)0,(coord)0);
	return intersects(prism, intersection);
}