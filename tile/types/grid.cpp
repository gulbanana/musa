#include <tile/stdafx.h>
#include "grid.h"

grid::grid(unsigned int x, unsigned int y) : width(x), height(y)
{
	buffer = (tile**)malloc(x * y * sizeof(tile));
	
	for (unsigned int i = 0; i < x; i++)
		for (unsigned int j = 0; j < x; j++)
			buffer[x][y].value = '.';
}

grid::~grid()
{
	free(buffer);
}