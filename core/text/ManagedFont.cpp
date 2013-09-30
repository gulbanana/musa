#include <core/stdafx.h>
#include <cstdlib>
#include "ManagedFont.h"

ManagedFont::ManagedFont()
{
	memset(&font, 0, sizeof(stbtt_fontinfo));
	memset(&lut, 0, HASH_LUT_SIZE * sizeof(int));

	data = nullptr;
	glyphs = nullptr;

	datasize = 0;
	nglyphs = 0;

	ascender = 0.f;
	descender = 0.f;
	lineh = 0.f;
}

ManagedFont::~ManagedFont()
{
	if (glyphs)
		free(glyphs);
	if (data)
		free(data);
}