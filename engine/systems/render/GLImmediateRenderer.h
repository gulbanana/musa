#pragma once
#include <engine/geometry.h>
#include "scene.h"

class GLImmediateRenderer : public IRenderer
{
	SDL_Surface* _surface;
	bool _wireframe;	
	int _viewport_width;
	int _viewport_height;
	point _at_location;
	angles _at_orientation;

	void with_modelobject(std::function<void(void)>);

public:
	GLImmediateRenderer(bool wireframe);
	~GLImmediateRenderer();

	void set_viewport(int width, int height) final;
	void with_position(point location, angles orientation) final;
	void begin_frame() final;
	void end_frame() final;

	//models
	void arrive(SpriteMesh const*) final;
	void visit(SpriteMesh const*) final;
	void arrive(FVMesh const*) final;
	void visit(FVMesh const*) final;

	//transforms
	void arrive(OrthographicCamera const*) final;
	void visit(OrthographicCamera const*) final;
	void arrive(PerspectiveCamera const*) final;
	void visit(PerspectiveCamera const*) final;

	//materials
	void visit(SolidColourBrush const*) final;
};

