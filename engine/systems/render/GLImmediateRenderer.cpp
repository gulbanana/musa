#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include <SDL_video.h>
#include <SDL_opengl.h>
#include <boost/graph/adjacency_list.hpp>
#include "GLImmediateRenderer.h"

const int resolution = 30;
const float arc = (float)(2 * M_PI / resolution);

GLImmediateRenderer::GLImmediateRenderer(bool flat, int width, int height) : _orthographic(flat)
{
	//SDL init
	int rc; 
	rc = SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (rc != 0) throw std::runtime_error("failed to init doublebuffering");
	rc = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); 
	if (rc != 0) throw std::runtime_error("failed to init multisampling");
	rc = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	if (rc != 0) throw std::runtime_error("failed to init multisampling");

	_surface = SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_RESIZABLE);
	if (_surface == nullptr) throw std::runtime_error("failed to init gl context");

	//GL init
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (!_orthographic)
		glEnable(GL_DEPTH_TEST | GL_ALPHA_TEST);

	//set background colour
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	resize(width, height);
}


GLImmediateRenderer::~GLImmediateRenderer()
{
}

void GLImmediateRenderer::resize(int width, int height)
{
	//setup device-space
	glViewport(0, 0, width, height);

	//setup world-space
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	//setup clipping-space 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (_orthographic)
	{
		glOrtho(0.f, width, height, 0.f, -300.f, 300.f);	
	}

	else
	{
		auto fov = 1;
		auto depth = 300;
		auto fovRadians = fov * (float)M_PI / 180;
		auto nearPlane = (height / 2.f) / tanf(fovRadians / 2.f);
		auto farPlane = nearPlane + depth;
		auto centrePlane = -(nearPlane + depth/2);
		glFrustum(0, width, 0, height, nearPlane, farPlane);

		glMatrixMode(GL_MODELVIEW);				
		glTranslatef(0.f, 0.f, centrePlane);	//move all objects to the 1=1 frustum slice
	}
}

void GLImmediateRenderer::begin_frame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
}

void GLImmediateRenderer::end_frame()
{
	SDL_GL_SwapBuffers();
}


void GLImmediateRenderer::begin_modelobject(Color4F brush, Vector3F position, Vector3F orientation)
{
	glPushMatrix();

	glTranslatef(position.x, position.y, 0.f);

	glRotatef(orientation.x, 1.f, 0.f, 0.f);
	glRotatef(orientation.y, 0.f, 1.f, 0.f);
	glRotatef(orientation.z, 0.f, 0.f, 1.f);

	//brush
	glColor4f(brush.red, brush.green, brush.blue, brush.alpha);
}

void GLImmediateRenderer::end_modelobject()
{
	glPopMatrix();
}

void GLImmediateRenderer::visit(FVMesh const* mesh, Color4F brush, Vector3F position, Vector3F orientation)
{
	begin_modelobject(brush, position, orientation);
	
	//draw each face

	
	glBegin(GL_QUADS);
		//cube_vertices(mesh);
	glEnd();

	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_LINES);
		//cube_vertices(mesh);
	glEnd();

	end_modelobject();
}

void GLImmediateRenderer::visit(VVMesh const* mesh, Color4F brush, Vector3F position, Vector3F orientation)
{
	begin_modelobject(brush, position, orientation);
	
	//calculate faces
	//draw each face
	glBegin(GL_TRIANGLES);
	for (auto v : mesh->vertices)
	{
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();

	end_modelobject();
}