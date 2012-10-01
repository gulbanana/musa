#include <algorithm>
#include "Rect4F.h"
using namespace std;

Rect4F Rect4F::unification(Rect4F const& a, Rect4F const& b)
{
	return Rect4F(max(a.x1,b.x1), max(a.y1,b.y1), max(a.x2,b.x2), max(a.y2,b.y2));
}

bool Rect4F::contains(float x, float y) const
{
    return (x >= x1) && (x < x2) && (y >= y1) && (y < y2);
}

bool Rect4F::contains(Vector2F const& point) const
{
    return contains(point.x, point.y);
}

bool Rect4F::intersects(Rect4F const& rectangle) const
{
    Rect4F intersection(0.f,0.f,0.f,0.f);
    return intersects(rectangle, intersection);
}


bool Rect4F::intersects(Rect4F const& rectangle, Rect4F& intersection) const
{
    // Compute the intersection boundaries
    auto interLeft = max(x1, rectangle.x1);
    auto interBottom = max(y1, rectangle.y1);
    auto interRight = min(x2, rectangle.x2);
    auto interTop = min(y2, rectangle.y2);

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interBottom < interTop))
    {
        intersection = Rect4F(interLeft, interBottom, interRight, interTop);
        return true;
    }
    else
    {
        intersection = Rect4F(0.f, 0.f, 0.f, 0.f);
        return false;
    }
}

Rect4F Rect4F::operator+(Vector2F const& p)
{
	return Rect4F(
		x1 + p.x,
		y1 + p.y,
		x2 + p.x,
		y2 + p.y
	);
}