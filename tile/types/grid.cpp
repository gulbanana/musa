#include <tile/stdafx.h>
#include <cstdlib>
#include "grid.h"
using namespace std;

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

void grid::fill(tile t)
{
	for (unsigned int i = 0; i < width; i++)
		for (unsigned int j = 0; j < height; j++)
			buffer[j*width+i] = t;
}

void grid::draw(tile t, unsigned int x, unsigned int y)
{
	buffer[y*width+x] = t;
}

void grid::draw(grid g, unsigned int x, unsigned int y)
{
}

void grid::draw(string s, unsigned int x, unsigned int y)
{
	for (int i = 0; i < s.length(); i++)
		buffer[y*width+x + i] = tile(s[i]);
}