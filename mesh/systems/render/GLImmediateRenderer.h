#pragma once
#include <mesh/geometry.h>
#include <SDL_video.h>
#include "scene.h"

class GLImmediateRenderer : public IRenderer
{
	SDL_Surface* _surface;
	bool _wireframe;	
	int _viewport_width;
	int _viewport_height;

	//current transform
	point _at;
	rotation _facing;
	lnseg _scale;

public:
	GLImmediateRenderer(bool wireframe);
	~GLImmediateRenderer();

	void set_viewport(int width, int height) final;
	void set_transform(point translation, rotation r, lnseg scaling) final;
	void begin_frame() final;
	void end_frame() final;

	//models
	void visit_enter(SpriteMesh const*) final;
	void visit_leave(SpriteMesh const*) final;
	void visit_enter(FVMesh const*) final;
	void visit_leave(FVMesh const*) final;

	//transforms
	void visit_enter(OrthographicCamera const*) final;
	void visit_leave(OrthographicCamera const*) final;
	void visit_enter(PerspectiveCamera const*) final;
	void visit_leave(PerspectiveCamera const*) final;

	//materials
	void visit(SolidColourBrush const*) final;
};

