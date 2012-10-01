#include "GLImmediateRenderer.h"


GLImmediateRenderer::GLImmediateRenderer(void)
{
}


GLImmediateRenderer::~GLImmediateRenderer(void)
{
}
const int resolution = 32;
const float arc = (float)(2 * M_PI / resolution);

Circle::Circle(float r) : radius(r) {}

Rect4F Circle::bounds2D()
{
	return Rect4F(-radius, -radius, radius, radius);
}

void Circle::draw()
{
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.f, 0.f);
		for (int i = 0; i <= resolution; i++)
			glVertex2f(cos(i * arc)*radius, sin(i * arc)*radius);	
	glEnd();
}

#include <SDL_opengl.h>
#include "Rectangle.h"

Rect4F Rectangle::bounds2D()
{
	return bounds;
}

void Rectangle::draw()
{
	glBegin(GL_QUADS);
		glVertex2f(bounds.left(), bounds.top());
		glVertex2f(bounds.right(), bounds.top());
		glVertex2f(bounds.right(), bounds.bottom());
		glVertex2f(bounds.left(), bounds.bottom());
	glEnd();
}

