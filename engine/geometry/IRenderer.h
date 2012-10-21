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
	virtual void set_transform(point translation, angles rotation, glm::vec3 scale) {}

	virtual void begin_frame() {}
	virtual void end_frame() {}

	//models
	virtual void visit_enter(SpriteMesh const*) = 0;
	virtual void visit_leave(SpriteMesh const*) = 0;
	virtual void visit_enter(FVMesh const*) = 0;
	virtual void visit_leave(FVMesh const*) = 0;

	//transforms
	virtual void visit_enter(OrthographicCamera const*) = 0;
	virtual void visit_leave(OrthographicCamera const*)  = 0;
	virtual void visit_enter(PerspectiveCamera const*) = 0;
	virtual void visit_leave(PerspectiveCamera const*)  = 0;

	//materials
	virtual void visit(SolidColourBrush const*) = 0;
};