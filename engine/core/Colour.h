#pragma once

class Colour
{
	Colour();

public:
	static const colour RED;
	static const colour GREEN;
	static const colour BLUE;
    static const colour CYAN;
	static const colour MAGENTA;
	static const colour YELLOW;
	static const colour BLACK;
	static const colour WHITE;
	static const colour TRANSLUCENT;
};

std::string to_string(colour);