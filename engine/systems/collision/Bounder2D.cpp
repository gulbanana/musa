#include "Bounder2D.h"

Rect4F Bounder2D::visit(CircleMesh* mesh)
{
	return Rect4F(-mesh->radius, -mesh->radius, mesh->radius, mesh->radius);
}

Rect4F Bounder2D::visit(RectangleMesh* mesh)
{
	return Rect4F(-mesh->bounds.width()/2,
				  -mesh->bounds.height()/2,
				  mesh->bounds.width()/2,
				  mesh->bounds.height()/2);
}

Rect4F Bounder2D::visit(FVMesh*) 
{
	auto boundingBox = Rect4F(0.f, 0.f, 0.f, 0.f);

	/* unimplemented
	for (auto& poly : polys)	
	{
		boundingBox = Rect4F::unify(boundingBox, poly->bounds2D());
	}
	*/

	return boundingBox;
}