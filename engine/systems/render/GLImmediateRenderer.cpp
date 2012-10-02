#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL_video.h>
#include <SDL_opengl.h>
#include "GLImmediateRenderer.h"

const int resolution = 30;
const float arc = (float)(2 * M_PI / resolution);

GLImmediateRenderer::GLImmediateRenderer(int width, int height)
{
	//init and set capabilities
	glEnable(GL_DEPTH_TEST | GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//specify window coordinates
	glViewport(0, 0, width, height);

	//set background colour
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//setup projection matrix - device coordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.f, width, height, 0.f, -300.f, 300.f);
	auto fov = 1;
	auto depth = 300;
	auto fovRadians = fov * (float)M_PI / 180;
	auto nearPlane = (height / 2.f) / tanf(fovRadians / 2.f);
	auto farPlane = nearPlane + depth;
	auto centrePlane = -(nearPlane + depth/2);
	glFrustum(0, width, 0, height, nearPlane, farPlane);

	//setup model matrix - object coordinates
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.f, 0.f, centrePlane);	//move all objects to the 1=1 frustum slice
}


GLImmediateRenderer::~GLImmediateRenderer()
{
}

/*void GLImmediateRenderer::visit(Sphere* mesh, Color4F brush, Vector3F position, Vector3F orientation)
{
	begin_modelobject(brush, position, orientation);

	//XXX this is not correct
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.f, 0.f);
		for (int i = 0; i <= resolution; i++)
			glVertex2f(cos(i * arc) * mesh->radius, sin(i * arc) * mesh->radius);	
	glEnd();

	end_modelobject();
}*/

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