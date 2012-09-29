#pragma once

namespace sf
{
	class Color;
}

class Color4F
{
public:

    float red;
    float blue;
	float green;
	float alpha;

	Color4F(float r, float g, float b, float a = 1.f);
	Color4F(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, unsigned __int8 a = 1.f); 

	static const Color4F RED;
	static const Color4F GREEN;
	static const Color4F BLUE;
    static const Color4F CYAN;
	static const Color4F MAGENTA;
	static const Color4F YELLOW;
	static const Color4F BLACK;
	static const Color4F WHITE;
	static const Color4F TRANSLUCENT;
};
