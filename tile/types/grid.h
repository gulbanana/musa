#pragma once
#include "tile.h"

//low-level tile grid
//this is the most primitive tile storage abstraction, used directly
//by the renderer, so it has to be fairly fast - but still memory-safe
//as long as you don't e.g. mess with its allocated buffer
struct grid
{
	unsigned int width;
	unsigned int height;
	tile* buffer;

	grid(unsigned int x, unsigned int y); 
	~grid();

	void resize(unsigned int x, unsigned int y);

	void fill(tile t);

	void draw(tile t, unsigned int x, unsigned int y);
	void draw(grid g, unsigned int x, unsigned int y);

	void draw(std::string text, unsigned int x, unsigned int y);
    void draw(std::string text, unsigned int x, unsigned int y, colour c);
	void draw(std::string text, unsigned int x, unsigned int y, font_weight w);
    void draw(std::string text, unsigned int x, unsigned int y, colour c, font_weight w);
};