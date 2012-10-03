#pragma once
#include <engine/core.h>

struct VVMesh;
struct FVMesh;

class IRenderer
{

public:
	virtual ~IRenderer() {}

	//optional operations
	virtual void resize(int width, int height) {}
	virtual void begin_frame() {}
	virtual void end_frame() {}

	//required operations
	virtual void visit(VVMesh const*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
	virtual void visit(FVMesh const*, Color4F brush, Vector3F position, Vector3F orientation) = 0;
};