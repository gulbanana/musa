#pragma once
#include <string>
#include <stdint.h>

class Colour4F
{
public:

    float red;
    float blue;
	float green;
	float alpha;

	Colour4F(float r, float g, float b, float a = 1.f);
	Colour4F(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	static const Colour4F RED;
	static const Colour4F GREEN;
	static const Colour4F BLUE;
    static const Colour4F CYAN;
	static const Colour4F MAGENTA;
	static const Colour4F YELLOW;
	static const Colour4F BLACK;
	static const Colour4F WHITE;
	static const Colour4F TRANSLUCENT;
};

std::string to_string(Colour4F);