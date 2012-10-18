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

	//objects
	virtual void draw(SpriteMesh const*) = 0;
	virtual void draw(FVMesh const*) = 0;

	//materials
	virtual void paint(SolidColourBrush const*) = 0;

	//transforms
	virtual void morph(OrthographicCamera const*) = 0;
	virtual void unmorph(OrthographicCamera const*)  = 0;
	virtual void morph(PerspectiveCamera const*) = 0;
	virtual void unmorph(PerspectiveCamera const*)  = 0;
};