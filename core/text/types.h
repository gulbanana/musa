#pragma once

enum class font_weight 
{
	REGULAR = 0,
	BOLD,
	ITALIC,
	BOLD_ITALIC
};

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