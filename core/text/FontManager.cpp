#include <core/stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_opengl.h>
#include "FontManager.h"
#include "ManagedFont.h"
#include "stb_truetype.h"
#include "utf8.h"

#define MAX_ROWS 128
#define MAX_FONTS 4
#define VERT_COUNT (6*1)
#define VERT_STRIDE (sizeof(float)*4)

struct quad8
{
	float x0, y0, s0, t0;
	float x1, y1, s1, t1;
};

struct row3
{
	short x;
	short y;
	short h;	
};

class FontManagerImpl
{
private:
	bool _drawing;

	row3 rows[MAX_ROWS];
	int nrows;

	float verts[4*VERT_COUNT];
	int nverts;

	int _texture_width;
	int _texture_height;
	float _inverse_texture_width;
	float _inverse_texture_height;
	GLuint _texture;

	ManagedFont fonts[MAX_FONTS];

	unsigned int hashint(unsigned int a);
	float* setv(float* v, float x, float y, float s, float t);
	Glyph* get_glyph(struct ManagedFont* fnt, unsigned int codepoint, short isize);
	int get_quad(struct ManagedFont* fnt, unsigned int codepoint, short isize, float* x, float* y, quad8* q);
	void flush_draw();

public:
	FontManagerImpl(int cachew, int cacheh);
	~FontManagerImpl();

	int add_font(int idx, const char* path);

	void begin_draw();
	float draw_cstring(int idx, float size, float x, float y, const char* string);
	float draw_character(int idx, float size, float x, float y, char character);
	void end_draw();
	
	dimensions get_text_dimensions(int idx, float size, const char* string);
	vmetrics get_vertical_metrics(int idx, float size);
	hmetrics get_horizontal_metrics(int idx, float size, char glyph);
};

FontManager::FontManager(int atlas_width, int atlas_height) : pimpl(new FontManagerImpl(atlas_width, atlas_height)) {}
FontManagerImpl::FontManagerImpl(int atlas_width, int atlas_height)
{
	_drawing = false;

	//create texture to act as a font atlas
	_texture_width = atlas_width;
	_texture_height = atlas_height;
	_inverse_texture_width = 1.0f/atlas_width;
	_inverse_texture_height = 1.0f/atlas_height;

	_texture = 0;
	glGenTextures(1, &_texture);
	if (!_texture) throw new std::runtime_error("failed to generate font atlas");

	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _texture_width, _texture_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//setup internal texture pointers
	nrows = 0;
	memset(rows, 0, sizeof(rows));
	nverts = 0;
	memset(verts, 0, sizeof(verts));
}

FontManager::~FontManager() { delete pimpl; }
FontManagerImpl::~FontManagerImpl()
{
	if (_texture) glDeleteTextures(1, &_texture);
}

int FontManager::add_font(int idx, const char* path) { return pimpl->add_font(idx, path); }
int FontManagerImpl::add_font(int idx, const char* path)
{
	FILE* fp = 0;
	int i, ascent, descent, fh, lineGap;
	struct ManagedFont* fnt;
	
	if (idx < 0 || idx >= MAX_FONTS) return 0;
	
	fnt = &fonts[idx];
	if (fnt->data)
		free(fnt->data);
	if (fnt->glyphs)
		free(fnt->glyphs);
	memset(fnt, 0, sizeof(ManagedFont));
	
	// Init hash lookup.
	for (i = 0; i < HASH_LUT_SIZE; ++i) fnt->lut[i] = -1;
	
	// Read in the font data.
	auto err = fopen_s(&fp, path, "rb");
	if (err != 0) goto error;
	fseek(fp,0,SEEK_END);
	fnt->datasize = (int)ftell(fp);
	fseek(fp,0,SEEK_SET);
	fnt->data = (unsigned char*)malloc(fnt->datasize);
	if (fnt->data == NULL) goto error;
	fread(fnt->data, 1, fnt->datasize, fp);
	fclose(fp);
	fp = 0;
	
	// Init stb_truetype
	if (!stbtt_InitFont(&fnt->font, fnt->data, 0)) goto error;
	
	// Store normalized line height. The real line height is got
	// by multiplying the lineh by font size.
	stbtt_GetFontVMetrics(&fnt->font, &ascent, &descent, &lineGap);
	fh = ascent - descent;
	fnt->ascender = (float)ascent / (float)fh;
	fnt->descender = (float)descent / (float)fh;
	fnt->lineh = (float)(fh + lineGap) / (float)fh;
	
	return 1;
	
error:
	if (fnt->data) free(fnt->data);
	if (fnt->glyphs) free(fnt->glyphs);
	memset(fnt,0,sizeof(struct ManagedFont));
	if (fp) fclose(fp);
	return 0;
}

void FontManager::begin_draw() { pimpl->begin_draw(); }
void FontManagerImpl::begin_draw()
{
	if (_drawing)
		flush_draw();
	_drawing = true;
}

void FontManager::end_draw() { pimpl->end_draw(); }
void FontManagerImpl::end_draw()
{
	if (!_drawing) return;

/*
	// Debug dump.
	if (stash->nverts+6 < VERT_COUNT)
	{
		float x = 500, y = 100;
		float* v = &stash->verts[stash->nverts*4];

		v = setv(v, x, y, 0, 0);
		v = setv(v, x+stash->_texture_width, y, 1, 0);
		v = setv(v, x+stash->_texture_width, y+stash->th, 1, 1);

		v = setv(v, x, y, 0, 0);
		v = setv(v, x+stash->_texture_width, y+stash->th, 1, 1);
		v = setv(v, x, y+stash->th, 0, 1);

		stash->nverts += 6;
	}
*/
	
	flush_draw();
	_drawing = false;
}

float FontManager::draw_string(int fontIndex, float size, float x, float y, std::string s) { return pimpl->draw_cstring(fontIndex, size, x, y, s.c_str()); }
float FontManager::draw_cstring(int fontIndex, float size, float x, float y, const char* s) { return pimpl->draw_cstring(fontIndex, size, x, y, s); }
float FontManagerImpl::draw_cstring(int idx, float size, float x, float y, const char* s)
{
	unsigned int codepoint;
	unsigned int state = 0;
	struct quad8 q;
	short isize = (short)(size*10.0f);
	float* v;
	struct ManagedFont* fnt;
	
	if (idx < 0 || idx >= MAX_FONTS) return x;
	fnt = &fonts[idx];
	if (!fnt->data) return x;
	
	for (; *s; ++s)
	{
		if (decutf8(&state, &codepoint, *(unsigned char*)s)) continue;

		if (nverts+6 >= VERT_COUNT)
			flush_draw();
		
		if (!get_quad(fnt, codepoint, isize, &x, &y, &q)) continue;
		
		v = &verts[nverts*4];
		
		v = setv(v, q.x0, q.y0, q.s0, q.t0);
		v = setv(v, q.x1, q.y0, q.s1, q.t0);
		v = setv(v, q.x1, q.y1, q.s1, q.t1);

		v = setv(v, q.x0, q.y0, q.s0, q.t0);
		v = setv(v, q.x1, q.y1, q.s1, q.t1);
		v = setv(v, q.x0, q.y1, q.s0, q.t1);
		
		nverts += 6;		
	}
	
	return x;
}

float FontManager::draw_character(int fontIndex, float size, float x, float y, char c) { return pimpl->draw_character(fontIndex, size, x, y, c); }
float FontManagerImpl::draw_character(int idx, float size, float x, float y, char c)
{
	unsigned int codepoint;
	unsigned int state = 0;
	struct quad8 q;
	short isize = (short)(size*10.0f);
	float* v;
	struct ManagedFont* fnt;
	
	if (idx < 0 || idx >= MAX_FONTS) return x;
	fnt = &fonts[idx];
	if (!fnt->data) return x;
	
	if (decutf8(&state, &codepoint, (unsigned char)c)) return x;

	if (nverts+6 >= VERT_COUNT)
		flush_draw();
		
	if (!get_quad(fnt, codepoint, isize, &x, &y, &q)) return x;
		
	v = &verts[nverts*4];
		
	v = setv(v, q.x0, q.y0, q.s0, q.t0);
	v = setv(v, q.x1, q.y0, q.s1, q.t0);
	v = setv(v, q.x1, q.y1, q.s1, q.t1);

	v = setv(v, q.x0, q.y0, q.s0, q.t0);
	v = setv(v, q.x1, q.y1, q.s1, q.t1);
	v = setv(v, q.x0, q.y1, q.s0, q.t1);
		
	nverts += 6;		
	
	return x;
}

dimensions FontManager::get_text_dimensions(int idx, float size, const char* s) { return pimpl->get_text_dimensions(idx, size, s); }
dimensions FontManagerImpl::get_text_dimensions(int idx, float size, const char* s)
{
	unsigned int codepoint;
	unsigned int state = 0;
	struct quad8 q;
	short isize = (short)(size*10.0f);
	struct ManagedFont* fnt;
	float x = 0, y = 0;
	float minx, maxx, miny, maxy;
	
	if (idx < 0 || idx >= MAX_FONTS) throw new std::runtime_error("font index out of range");
	fnt = &fonts[idx];
	if (!fnt->data) throw new std::runtime_error("font not loaded");;
	
	minx = maxx = x;
	miny = maxy = y;

	for (; *s; ++s)
	{
		if (decutf8(&state, &codepoint, *(unsigned char*)s)) continue;
		if (!get_quad(fnt, codepoint, isize, &x, &y, &q)) continue;
		if (q.x0 < minx) minx = q.x0;
		if (q.x1 > maxx) maxx = q.x1;
		if (q.y1 < miny) miny = q.y1;
		if (q.y0 > maxy) maxy = q.y0;
	}

	return dimensions(minx, miny, maxx, maxy);
}

vmetrics FontManager::get_vertical_metrics(int idx, float size) { return pimpl->get_vertical_metrics(idx, size); }
vmetrics FontManagerImpl::get_vertical_metrics(int idx, float size)
{
	if (idx < 0 || idx >= MAX_FONTS) throw new std::runtime_error("font index out of range");
	if (!fonts[idx].data) throw new std::runtime_error("font not loaded");

	return vmetrics(fonts[idx].ascender*size, fonts[idx].descender*size, fonts[idx].lineh*size);
}

hmetrics FontManager::get_horizontal_metrics(int idx, float size, char glyph) { return pimpl->get_horizontal_metrics(idx, size, glyph); }
hmetrics FontManagerImpl::get_horizontal_metrics(int idx, float size, char glyph)
{
	unsigned int state = 0;
	unsigned int codepoint = 0;
	short isize = (short)(size*10.0f);

	decutf8(&state, &codepoint, (unsigned char)glyph);

	auto g = get_glyph(&fonts[idx], codepoint, isize);

	return hmetrics(g->xadv);
}

struct Glyph* FontManagerImpl::get_glyph(struct ManagedFont* fnt, unsigned int codepoint, short isize)
{
	int advance, lsb, x0, y0, x1, y1;
	float scale;
	struct Glyph* glyph;
	unsigned char* bmp;
	unsigned int h;
	float size = isize / 10.0f;
	struct row3* br;

	// Find code point and size.
	h = hashint(codepoint) & (HASH_LUT_SIZE-1);
	int i = fnt->lut[h];
	while (i != -1)
	{
		if (fnt->glyphs[i].codepoint == codepoint && fnt->glyphs[i].size == isize)
			return &fnt->glyphs[i];
		i = fnt->glyphs[i].next;
	}
	
	// Could not find glyph, create it.
	scale = stbtt_ScaleForPixelHeight(&fnt->font, size);
	int g = stbtt_FindGlyphIndex(&fnt->font, codepoint);
	stbtt_GetGlyphHMetrics(&fnt->font, g, &advance, &lsb);
	stbtt_GetGlyphBitmapBox(&fnt->font, g, scale,scale, &x0,&y0,&x1,&y1);
	int gw = x1 - x0;
	int gh = y1 - y0;


	// Find row where the glyph can be fit.
	br = NULL;
	int rowHeight = (gh+7) & ~7;
	for (i = 0; i < nrows; ++i)
	{
		if (rows[i].h == rowHeight && rows[i].x+gw+1 <= _texture_width)
			br = &rows[i];
	}
	
	// If no row found, add new.
	if (br == NULL)
	{
		short py = 0;
		// Check that there is enough space.
		if (nrows)
		{
			py = rows[nrows-1].y + rows[nrows-1].h+1;
			if (py + rowHeight > _texture_height)
				return 0;
		}
		// Init and add row
		br = &rows[nrows];
		br->x = 0;
		br->y = py;
		br->h = rowHeight;
		nrows++;
	}
	
	// Alloc space for new glyph.
	fnt->nglyphs++;
	fnt->glyphs = (Glyph*)realloc(fnt->glyphs, fnt->nglyphs*sizeof(Glyph));
	if (!fnt->glyphs) return 0;

	// Init glyph.
	glyph = &fnt->glyphs[fnt->nglyphs-1];
	memset(glyph, 0, sizeof(Glyph));
	glyph->codepoint = codepoint;
	glyph->size = isize;
	glyph->x0 = br->x;
	glyph->y0 = br->y;
	glyph->x1 = glyph->x0+gw;
	glyph->y1 = glyph->y0+gh;
	glyph->xadv = scale * advance;
	glyph->xoff = (float)x0;
	glyph->yoff = (float)y0;
	glyph->next = 0;

	// Advance row location.
	br->x += gw+1;
	
	// Insert char to hash lookup.
	glyph->next = fnt->lut[h];
	fnt->lut[h] = fnt->nglyphs-1;

	// Rasterize
	bmp = (unsigned char*)malloc(gw*gh);
	if (bmp)
	{
		stbtt_MakeGlyphBitmap(&fnt->font, bmp, gw,gh,gw, scale,scale, g);
		// Update texture
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		glTexSubImage2D(GL_TEXTURE_2D, 0, glyph->x0,glyph->y0, gw,gh, GL_ALPHA,GL_UNSIGNED_BYTE,bmp); 
		free(bmp);
	}
	
	return glyph;
}

int FontManagerImpl::get_quad(struct ManagedFont* font, unsigned int codepoint, short isize, float* x, float* y, struct quad8* q)
{
	struct Glyph* glyph = get_glyph(font, codepoint, isize);
	if (!glyph) return 0;
	
	//take the floor, keep intermediates in ints, do some maths, then convert back
	int rx = (int)floorf(*x + glyph->xoff);
	int ry = (int)floorf(*y - glyph->yoff);
	
	q->x0 = (float)rx;
	q->y0 = (float)ry;
	q->x1 = (float)(rx + glyph->x1 - glyph->x0);
	q->y1 = (float)(ry - glyph->y1 + glyph->y0);
	
	q->s0 = (glyph->x0) * _inverse_texture_width;
	q->t0 = (glyph->y0) * _inverse_texture_height;
	q->s1 = (glyph->x1) * _inverse_texture_width;
	q->t1 = (glyph->y1) * _inverse_texture_height;
	
	*x += glyph->xadv;
	
	return 1;
}

void FontManagerImpl::flush_draw()
{
	if (nverts == 0)
		return;
		
	glBindTexture(GL_TEXTURE_2D, _texture);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, VERT_STRIDE, verts);
	glTexCoordPointer(2, GL_FLOAT, VERT_STRIDE, verts+2);
	glDrawArrays(GL_TRIANGLES, 0, nverts);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	nverts = 0;
}

unsigned int FontManagerImpl::hashint(unsigned int a)
{
	a += ~(a<<15);
	a ^=  (a>>10);
	a +=  (a<<3);
	a ^=  (a>>6);
	a += ~(a<<11);
	a ^=  (a>>16);
	return a;
}

float* FontManagerImpl::setv(float* v, float x, float y, float s, float t)
{
	v[0] = x;
	v[1] = y;
	v[2] = s;
	v[3] = t;
	return v+4;
}