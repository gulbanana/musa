#pragma once
#include "stb_truetype.h"

#define HASH_LUT_SIZE 256

struct Glyph
{
	unsigned int codepoint;
	short size;
	int x0,y0,x1,y1;
	float xadv,xoff,yoff;
	int next;
};

struct ManagedFont
{
	stbtt_fontinfo font;
	int lut[HASH_LUT_SIZE];
	unsigned char* data;
	struct Glyph* glyphs;
	int datasize;
	int nglyphs;
	float ascender;
	float descender;
	float lineh;

	ManagedFont();
	~ManagedFont();
};