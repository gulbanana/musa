#pragma once
#include <engine/core.h>

struct CircleMesh;
struct RectangleMesh;
struct FVMesh;

class IRenderer
{

public:
	virtual ~IRenderer() = 0 {}

	virtual void begin_frame() {}
	virtual void end_frame() {}

	virtual void visit(CircleMesh*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
	virtual void visit(RectangleMesh*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
	virtual void visit(FVMesh*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
};