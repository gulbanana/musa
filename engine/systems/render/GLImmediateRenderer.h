#pragma once
#include <engine/core.h>
#include <engine/geometry.h>

class GLImmediateRenderer : public IRenderer
{
	SDL_Surface* _surface;
	bool _orthographic;	
	bool _wireframe;	
	

	void with_modeltransform(Vec3<coord> position, Vec3<degrees> orientation, std::function<void(void)>);

public:
	GLImmediateRenderer(bool orthographic, bool wireframe);
	~GLImmediateRenderer();

	virtual void resize(int width, int height) override;

	virtual void begin_frame() override;
	virtual void end_frame() override;

	virtual void visit(SolidColourBrush const*) override;
	virtual void visit(SpriteMesh const*, Vec3<coord> position, Vec3<degrees> orientation) override;
	virtual void visit(FVMesh const*, Vec3<coord> position, Vec3<degrees> orientation) override;
};

