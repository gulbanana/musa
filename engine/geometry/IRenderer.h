#pragma once
#include <engine/core.h>

struct CircleMesh;
struct SphereMesh;
struct RectangleMesh;
struct RectangularPrismMesh;
struct FVMesh;

class IRenderer
{

public:
	virtual ~IRenderer() = 0 {}

	virtual void begin_frame() {}
	virtual void end_frame() {}

	virtual void visit(CircleMesh*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
	virtual void visit(SphereMesh*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
	virtual void visit(RectangleMesh*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
	virtual void visit(RectangularPrismMesh*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
	virtual void visit(FVMesh*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
};