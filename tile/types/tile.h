#pragma once
#include "colour.h"
#include <core/text/types.h>

//eventually these may be tested utf8- for now, ascii without a well-defined code page.
struct tile
{
	char value;
	colour shade;
	font_weight style;

	tile(char v):                          value(v), shade(colour::WHITE), style(font_weight::REGULAR) {}
	tile(char v, colour s):                value(v), shade(s),             style(font_weight::REGULAR) {}
	tile(char v, font_weight w):           value(v), shade(colour::WHITE), style(w) {}
	tile(char v, colour s, font_weight w): value(v), shade(s),             style(w) {}

	tile(tile const& that): value(that.value), shade(that.shade), style(that.style) {}

	void operator=(tile const& that) { value = that.value; shade = that.shade; style = that.style; }
};