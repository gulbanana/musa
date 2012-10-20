#pragma once

struct SpriteMesh;
struct FVMesh;

struct SolidColourBrush;

struct OrthographicCamera;
struct PerspectiveCamera;

class IRenderer
{
public:
	virtual ~IRenderer() {}

	//optional operations
	virtual void set_viewport(int width, int height) {}
	virtual void with_position(point location, angles orientation) {}

	virtual void begin_frame() {}
	virtual void end_frame() {}

	//models
	virtual void arrive(SpriteMesh const*) = 0;
	virtual void visit(SpriteMesh const*) = 0;
	virtual void arrive(FVMesh const*) = 0;
	virtual void visit(FVMesh const*) = 0;

	//transforms
	virtual void arrive(OrthographicCamera const*) = 0;
	virtual void visit(OrthographicCamera const*)  = 0;
	virtual void arrive(PerspectiveCamera const*) = 0;
	virtual void visit(PerspectiveCamera const*)  = 0;

	//materials
	virtual void visit(SolidColourBrush const*) = 0;
};