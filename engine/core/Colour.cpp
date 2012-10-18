#include <engine/core.h>
using namespace std;

const colour Colour::RED =         colour(1.f, 0.f, 0.f, 1.f);
const colour Colour::GREEN =       colour(0.f, 1.f, 0.f, 1.f);
const colour Colour::BLUE =        colour(0.f, 0.f, 1.f, 1.f);
const colour Colour::CYAN =        colour(0, 1.f, 1.f, 1.f);
const colour Colour::MAGENTA =     colour(1.f, 0.f, 1.f, 1.f);
const colour Colour::YELLOW =      colour(1.f, 1.f, 0.f, 1.f);
const colour Colour::BLACK =       colour(0.f, 0.f, 0.f, 1.f);
const colour Colour::WHITE =       colour(1.f, 1.f, 1.f, 1.f);
const colour Colour::TRANSLUCENT = colour(0.f, 0.0, 0.f, 0.f);

string to_string(colour c)
{
	return string("(") +
		to_string(c.r) + "|" +
		to_string(c.g) + "|" +
		to_string(c.b) + "|" +
		to_string(c.a) + ")";
}
