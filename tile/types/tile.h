#pragma once

//eventually these may be attributed, unicode, or anything else - for now, 
//ascii without a well-defined code page.
struct tile
{
	char value;

	tile(char v): value(v) {}
};