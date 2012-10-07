#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include <SDL_video.h>
#include <SDL_opengl.h>
#include <boost/graph/adjacency_list.hpp>
#include "GLImmediateRenderer.h"
using namespace std;

const int resolution = 30;
const float arc = (float)(2 * M_PI / resolution);

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
    
	//GL init
	glEnable(GL_BLEND | GL_DEPTH_TEST | GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//options
    if (_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.f, 0.f, 0.f, 0.f);
    
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
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
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
	glPushMatrix();

	glTranslatef(_at_location.x, _at_location.y, _at_location.z);

#if defined DOUBLE_PRECISION
	glRotated(_at_orientation.x, 1.0, 0.0, 0.0);
	glRotated(_at_orientation.y, 0.0, 1.0, 0.0);
	glRotated(_at_orientation.z, 0.0, 0.0, 1.0);
#else
	glRotatef(_at_orientation.x, 1.f, 0.f, 0.f);
	glRotatef(_at_orientation.y, 0.f, 1.f, 0.f);
	glRotatef(_at_orientation.z, 0.f, 0.f, 1.f);
#endif

	f();

	glPopMatrix();
}

void GLImmediateRenderer::morph(OrthographicCamera const* camera) 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glOrtho(
		camera->visible_world.left(), camera->visible_world.right(), 
		camera->visible_world.bottom(), camera->visible_world.top(),
		camera->visible_world.front(), camera->visible_world.back()		//near & far planes are flipped
	);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
#ifdef DOUBLE_PRECISION
	
	glRotated(_at_orientation.x, 1.0, 0.0, 0.0);
	glRotated(_at_orientation.y, 0.0, 1.0, 0.0);
	glRotated(_at_orientation.z, 0.0, 0.0, 1.0);
	glTranslated(_at_location.x, _at_location.y, _at_location.z);	
#else
	glTranslatef(-_at_location.x, -_at_location.y, -_at_location.z);	
	glRotatef(_at_orientation.x, 1.f, 0.f, 0.f);
	glRotatef(_at_orientation.y, 0.f, 1.f, 0.f);
	glRotatef(_at_orientation.z, 0.f, 0.f, 1.f);
#endif
}


void GLImmediateRenderer::morph(PerspectiveCamera const*)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	auto fov = 1;
		auto depth = 300;
		auto fovRadians = fov * (float)M_PI / 180;
		auto nearPlane = (_viewport_height / 2.f) / tanf(fovRadians / 2.f);
		auto farPlane = nearPlane + depth;
		auto centrePlane = -(nearPlane + depth/2);
		glFrustum(0, _viewport_width, 0, _viewport_height, nearPlane, farPlane);

		//move all objects to the 1=1 frustum slice
		glMatrixMode(GL_MODELVIEW);	
#ifdef DOUBLE_PRECISION
		glTranslated(0.0, 0.0, centrePlane);	
#else
		glTranslatef(0.f, 0.f, centrePlane);	
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
	glColor4f(brush->colour.red, brush->colour.green, brush->colour.blue, brush->colour.alpha);
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

