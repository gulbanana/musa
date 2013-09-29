#include <tile/stdafx.h>
#include "grid.h"

grid::grid(unsigned int x, unsigned int y) : width(x), height(y)
{
	buffer = (tile*)malloc(x * y * sizeof(tile));	
}

grid::~grid()
{
	free(buffer);
}

void grid::zero()
{
	for (unsigned int i = 0; i < width; i++)
		for (unsigned int j = 0; j < height; j++)
			buffer[i*width + j].value = '.';
}

void grid::resize(unsigned int x, unsigned int y)
{
	free(buffer);
	width = x;
	height = y;
	buffer = (tile*)malloc(x * y * sizeof(tile));
}