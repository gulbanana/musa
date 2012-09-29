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

