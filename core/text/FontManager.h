#pragma once

class FontManagerImpl;

struct vmetrics
{
	float ascender;
	float descender;
	float line_height;

	vmetrics(float a, float d, float l) : ascender(a), descender(d), line_height(l) {}
};

struct hmetrics
{
	float glyph_width;

	hmetrics(float w) : glyph_width(w) {}
};

struct dimensions
{
	float minX;
	float minY;
	float maxX;
	float maxY;

	dimensions(float _minX, float _minY, float _maxX, float _maxY) : minX(_minX), minY(_minY), maxX(_maxX), maxY(_maxY) {}
};

//this must not be created until *after* GL has been initialised
class FontManager
{
private:
	FontManagerImpl* pimpl;

public:
	FontManager(int cacheW, int cacheH);
	~FontManager();

	int add_font(int index, const char* path);

	void begin_draw();
	float draw_string(int index, float size, float x, float y, std::string string);
	float draw_cstring(int index, float size, float x, float y, const char* string);
	float draw_character(int index, float size, float x, float y, char character);
	void end_draw();
	
	dimensions get_text_dimensions(int idx, float size, const char* string);
	vmetrics get_vertical_metrics(int idx, float size);
	hmetrics get_horizontal_metrics(int idx, float size, char glyph);
};