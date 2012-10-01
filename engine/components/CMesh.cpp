#include "CGeometry2D.h"

CGeometry2D::CGeometry2D(Color4F c, std::unique_ptr<IRenderable<Rect4F>> p) :  polys(), color(c)
{
    polys.push_back(std::move(p));
}

Rect4F CGeometry2D::bounds()
{
	auto boundingBox = Rect4F(0.f, 0.f, 0.f, 0.f);

	for (auto& poly : polys)	
	{
		boundingBox = Rect4F::unify(boundingBox, poly->bounds2D());
	}

	return boundingBox;
}