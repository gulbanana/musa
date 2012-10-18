#include <engine/core.h>
#include <stdexcept>
#include <functional>
#include <SDL_video.h>
#include <SDL_opengl.h>
#include "GLImmediateRenderer.h"
using namespace std;

GLImmediateRenderer::GLImmediateRenderer(bool wireframe) 
	: _wireframe(wireframe), _at_location((coord)0,(coord)0,(coord)0), _at_orientation((degrees)0,(degrees)0,(degrees)0)
{
	//SDL init
	int rc; 
	rc = SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (rc != 0) throw runtime_error("failed to init doublebuffering");
	rc = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); 
	if (rc != 0) throw runtime_error("failed to init multisampling");
	rc = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	if (rc != 0) throw runtime_error("failed to init multisampling");
	rc = SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); 
	if (rc != 0) throw runtime_error("failed to init depth buffer");
}


GLImmediateRenderer::~GLImmediateRenderer()
{
}

void GLImmediateRenderer::set_viewport(int width, int height)
{
	_viewport_width = width;
	_viewport_height = height;

    //might be able to avoid this with sdl 2.0..
	_surface = SDL_SetVideoMode(_viewport_width, _viewport_height, 32, SDL_OPENGL | SDL_RESIZABLE);
	if (_surface == nullptr) throw std::runtime_error("failed to init gl context");
    
	//alpha blending, depth testing
	
	//glDisable();

	//rgba translucency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//??
	glShadeModel(GL_SMOOTH);

	//black background
	glClearColor(0.f, 0.f, 0.f, 0.f);
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	//depth buffer config
	//glDepthFunc(GL_LEQUAL);
	//glClearDepth(1.0);
	//glDepthMask(GL_TRUE);

	//back-face fragment culling
    //glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	//setup device-space
	glViewport(0, 0, width, height);

	//setup world-space
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	//setup clipping-space 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void GLImmediateRenderer::begin_frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLImmediateRenderer::end_frame()
{
	SDL_GL_SwapBuffers();
	//glGetError()
}

void GLImmediateRenderer::with_position(Vec3<coord> location, Vec3<degrees> orientation) 
{
	_at_location = location;
	_at_orientation = orientation;
}

void GLImmediateRenderer::with_modelobject(std::function<void(void)> f)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

#if defined DOUBLE_PRECISION
	glTranslated(_at_location.x, _at_location.y, _at_location.z);

	glRotated(_at_orientation.x, 1.0, 0.0, 0.0);
	glRotated(_at_orientation.y, 0.0, 1.0, 0.0);
	glRotated(_at_orientation.z, 0.0, 0.0, 1.0);
#else
	glTranslatef(_at_location.x, _at_location.y, _at_location.z);

	glRotatef(_at_orientation.x, 1.f, 0.f, 0.f);
	glRotatef(_at_orientation.y, 0.f, 1.f, 0.f);
	glRotatef(_at_orientation.z, 0.f, 0.f, 1.f);
#endif

	f();

	glPopMatrix();
}

void GLImmediateRenderer::morph(OrthographicCamera const* camera) 
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	coord viewportAR = (coord)_viewport_width / (coord)_viewport_height;
	coord cameraAR = camera->range.width() / camera->range.height();
	coord l, r, b, t;

	//calculate planes based on scaling mode
	switch (camera->widescreen)
	{
	case ScaleMethod::HorPlus:
		b = camera->range.bottom();
		t = camera->range.top();
		l = (camera->range.width() - (camera->range.width() / cameraAR * viewportAR)) / 2;
		r = camera->range.width() / cameraAR * viewportAR + l;
		break;

	case ScaleMethod::VertMinus:
		l = camera->range.left();
		r = camera->range.right();
		b = (camera->range.height() - (camera->range.height() * cameraAR / viewportAR)) / 2;
		t = camera->range.height() * cameraAR / viewportAR + b;
		break;

	case ScaleMethod::Anamorphic:
		throw runtime_error("letterboxing not implemented");
		break;

	case ScaleMethod::Stretch:
	default:
		l = camera->range.left();
		r = camera->range.right();
		b = camera->range.bottom();
		t = camera->range.top();
		break;
	}

	glOrtho(l, r, b, t, camera->range.front(), camera->range.back());

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#ifdef DOUBLE_PRECISION
	glTranslated(camera->range.right()/2 -_at_location.x, camera->range.top()/2 -_at_location.y, -_at_location.z);	
#else
	glTranslatef(camera->range.right()/2 -_at_location.x, camera->range.top()/2 -_at_location.y, -_at_location.z);	
#endif
	//TODO: rotation?
}

/*
                  y       tan(vertical FOV/2)
aspect ratio  =  ---  =  ---------------------
				  x      tan(horizontal FOV/2)
*/
void GLImmediateRenderer::morph(PerspectiveCamera const* camera)
{
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	const coord eyeDistance = camera->dof / 1024;

	//Select clipping planes based on FOV and scaling method
	auto aspect = maths::aspect_ratio(_viewport_width, _viewport_height);
	switch (camera->widescreen)
	{
		case ScaleMethod::HorPlus:
		{
			auto planes = maths::vertical_perspective(camera->fov, aspect, eyeDistance, eyeDistance + camera->dof);
			glFrustum(planes.left(), planes.right(), planes.bottom(), planes.top(), planes.front(), planes.back());
			break;
		}

		case ScaleMethod::VertMinus:
		{
			auto planes = maths::horizontal_perspective(camera->fov, aspect, eyeDistance, eyeDistance + camera->dof);
			glFrustum(planes.left(), planes.right(), planes.bottom(), planes.top(), planes.front(), planes.back());
			break;
		}

		case ScaleMethod::Stretch:
		case ScaleMethod::Anamorphic:
		default:
			throw runtime_error("scaling method not implemented by 3d renderer");
			break;
	}

	//add rotation matrices to the projection
#ifdef DOUBLE_PRECISION
	glRotated(_at_orientation.x, 1.0, 0.0, 0.0);
	glRotated(_at_orientation.y, 0.0, 1.0, 0.0);
	glRotated(_at_orientation.z, 0.0, 0.0, 1.0);
#else
	glRotatef(_at_orientation.x, 1.0, 0.0, 0.0);
	glRotatef(_at_orientation.y, 0.0, 1.0, 0.0);
	glRotatef(_at_orientation.z, 0.0, 0.0, 1.0);
#endif

	//move models to the "eye level" plane
	glMatrixMode(GL_MODELVIEW);	
	glPushMatrix();
#ifdef DOUBLE_PRECISION
	glTranslated(-_at_location.x, -_at_location.y, _at_location.z - camera->dof);
#else
	glTranslatef(-_at_location.x, -_at_location.y, _at_location.z - camera->dof);
#endif
}

void GLImmediateRenderer::unmorph(OrthographicCamera const*)
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);	
	glPopMatrix();
}

void GLImmediateRenderer::unmorph(PerspectiveCamera const*)
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);	
	glPopMatrix();
}

void GLImmediateRenderer::paint(SolidColourBrush const* brush)
{
	glColor4fv(&brush->colour[0]);
}

void GLImmediateRenderer::draw(SpriteMesh const* mesh)
{
	with_modelobject([=]
	{
	});
}

void GLImmediateRenderer::draw(FVMesh const* mesh)
{
	with_modelobject([=]
	{
		if (_wireframe || mesh->wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (mesh->sides == 3)
			glBegin(GL_TRIANGLES);
		else if (mesh->sides == 4)
			glBegin(GL_QUADS);
		else
			throw runtime_error("FVMesh has erroneous sides per face");	//TODO: or just do nothing?

		for (auto& group : mesh->groups)
		{
			group.brush->accept(this);

			for (auto& face : group.faces)
			{
				for (auto index : face.vertex_indices)
				{
					#ifdef DOUBLE_PRECISION
					glVertex3d(mesh->vertices[index].x, mesh->vertices[index].y, mesh->vertices[index].z);
					#else
					glVertex3f(mesh->vertices[index].x, mesh->vertices[index].y, mesh->vertices[index].z);
					#endif
				}
			}
		}

		glEnd();
	});
}

