#pragma once
#include <engine/core.h>
#include <engine/geometry.h>

class GLImmediateRenderer : public IRenderer
{
	SDL_Surface* _surface;
	bool _wireframe;	
	int _viewport_width;
	int _viewport_height;
	Vec3<coord> _at_location;
	Vec3<degrees> _at_orientation;

	void with_modelobject(std::function<void(void)>);

public:
	GLImmediateRenderer(bool wireframe);
	~GLImmediateRenderer();

	virtual void set_viewport(int width, int height) override;
	virtual void with_position(Vec3<coord> location, Vec3<degrees> orientation) override;

	virtual void begin_frame() override;
	virtual void end_frame() override;

	virtual void morph(OrthographicCamera const*) override;
	virtual void unmorph(OrthographicCamera const*) override;
	virtual void morph(PerspectiveCamera const*) override;
	virtual void unmorph(PerspectiveCamera const*) override;

	virtual void paint(SolidColourBrush const*) override;

	virtual void draw(SpriteMesh const*) override;
	virtual void draw(FVMesh const*) override;
};

