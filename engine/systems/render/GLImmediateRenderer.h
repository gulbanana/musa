#pragma once
#include <engine/core.h>
#include <engine/geometry.h>

class GLImmediateRenderer : public IRenderer
{
	bool _orthographic;	//2d?
	SDL_Surface* _surface;

	void begin_modelobject(Color4F brush, Vector3F position, Vector3F orientation);
	void end_modelobject();
public:
	GLImmediateRenderer(bool orthographic, int width, int height);
	~GLImmediateRenderer();

	virtual void resize(int width, int height) override;

	virtual void begin_frame() override;
	virtual void end_frame() override;

	virtual void visit(VVMesh const*, Color4F brush, Vector3F position, Vector3F orientation) override;
	virtual void visit(FVMesh const*, Color4F brush, Vector3F position, Vector3F orientation) override;
};

