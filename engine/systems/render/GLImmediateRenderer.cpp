#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL_video.h>
#include <SDL_opengl.h>
#include "GLImmediateRenderer.h"

const int resolution = 32;
const float arc = (float)(2 * M_PI / resolution);

GLImmediateRenderer::GLImmediateRenderer(int width, int height)
{
	//init and set capabilities
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//specify window coordinates
	glViewport(0, 0, width, height);

	//set background colour
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//create orthogonal projection matrix - device coordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.f, width, height, 0.f, -1.f, 1.f);

	//reset to standard matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


GLImmediateRenderer::~GLImmediateRenderer()
{
}

void GLImmediateRenderer::visit(CircleMesh* mesh, Color4F brush, Vector3F position, Vector3F orientation)
{
	begin_modelobject(brush, position, orientation);

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.f, 0.f);
		for (int i = 0; i <= resolution; i++)
			glVertex2f(cos(i * arc) * mesh->radius, sin(i * arc) * mesh->radius);	
	glEnd();

	end_modelobject();
}

void GLImmediateRenderer::visit(RectangleMesh* mesh, Color4F brush, Vector3F position, Vector3F orientation)
{
	begin_modelobject(brush, position, orientation);

	glBegin(GL_QUADS);
		glVertex2f(mesh->bounds.left(), mesh->bounds.top());
		glVertex2f(mesh->bounds.right(), mesh->bounds.top());
		glVertex2f(mesh->bounds.right(), mesh->bounds.bottom());
		glVertex2f(mesh->bounds.left(), mesh->bounds.bottom());
	glEnd();

	end_modelobject();
}

void GLImmediateRenderer::visit(FVMesh* mesh, Color4F brush, Vector3F position, Vector3F orientation)
{
	begin_modelobject(brush, position, orientation);
	//not implemented
	end_modelobject();
}

void GLImmediateRenderer::begin_frame()
{
	glClear(GL_COLOR_BUFFER_BIT);
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