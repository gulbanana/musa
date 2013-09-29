#include <tile/stdafx.h>
#include <cstdlib>
#include "grid.h"

grid::grid(unsigned int x, unsigned int y) : width(x), height(y)
{
	buffer = (tile*)malloc(x * y * sizeof(tile));	
}

grid::~grid()
{
	free(buffer);
}

void grid::resize(unsigned int x, unsigned int y)
{
	free(buffer);
	width = x;
	height = y;
	buffer = (tile*)malloc(x * y * sizeof(tile));
}

void grid::zero()
{
	for (unsigned int i = 0; i < width; i++)
		for (unsigned int j = 0; j < height; j++)
			buffer[j*width+i] = tile('.');
}

void grid::draw(tile t, unsigned int x, unsigned int y)
{
	buffer[y*width+x] = t;
}
void grid::draw(grid g, unsigned int x, unsigned int y)
{
}