#pragma once
#include "colour.h"

//eventually these may be attributed, unicode, or anything else - 
//for now, ascii without a well-defined code page.
struct tile
{
	char value;
	colour shade;

	tile(char v): value(v), shade(colour::WHITE) {}
	tile(char v, colour s): value(v), shade(s) {}

	tile(tile const& that): value(that.value), shade(that.shade) {}

	void operator=(tile const& that) { value = that.value; shade = that.shade; }
};