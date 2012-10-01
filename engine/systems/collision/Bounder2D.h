#pragma once
#include <engine/geometry.h>

class Bounder2D : public IBounder<Rect4F>
{
	Rect4F visit(CircleMesh*) override;
	Rect4F visit(RectangleMesh*) override;
	Rect4F visit(FVMesh*) override;
};