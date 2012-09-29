#include "CGeometry2D.h"

Rect4F CGeometry2D::bounds()
{
	auto boundingBox = Rect4F(0.f, 0.f, 0.f, 0.f);

	for (auto& poly : polys)	
	{
		boundingBox = Rect4F::unify(boundingBox, poly->bounds2D());
	}

	return boundingBox;
}