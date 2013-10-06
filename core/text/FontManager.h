#pragma once
#include "types.h"

class FontManagerImpl;

//this must not be created until *after* GL has been initialised,
//as it will create and bind textures during construction
class FontManager
{
private:
	FontManagerImpl* pimpl;

public:
	FontManager(int cacheW, int cacheH);
	~FontManager();

	int load_font(font_weight index, const char* path);

	void begin_draw();
	float draw_string(font_weight weight, float size, float x, float y, std::string string);
	float draw_cstring(font_weight weight, float size, float x, float y, const char* string);
	float draw_character(font_weight weight, float size, float x, float y, char character);
	void end_draw();
	
	dimensions get_text_dimensions(font_weight weight, float size, std::string string);
	vmetrics get_vertical_metrics(font_weight weight, float size);
	hmetrics get_horizontal_metrics(font_weight weight, float size, char glyph);
};