#pragma once
#include <engine/core.h>

struct SpriteMesh;
struct FVMesh;

struct SolidColourBrush;

class IRenderer
{
public:
	virtual ~IRenderer() {}

	//optional operations
	virtual void resize(int width, int height) {}
	virtual void begin_frame() {}
	virtual void end_frame() {}

	//objects
	virtual void visit(SpriteMesh const*, Vec3<coord> position, Vec3<degrees> orientation) = 0;
	virtual void visit(FVMesh const*, Vec3<coord> position, Vec3<degrees> orientation) = 0;

	//brushes
	virtual void visit(SolidColourBrush const*) = 0;
};