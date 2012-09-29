#include <SDL_opengl.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Circle.h"

const int resolution = 32;
const float arc = 2 * M_PI / resolution;

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
