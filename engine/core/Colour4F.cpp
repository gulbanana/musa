#include <engine/core.h>
#include "Colour4F.h"
using namespace std;

const Colour4F Colour4F::RED = Colour4F(1.f, 0.f, 0.f);
const Colour4F Colour4F::GREEN = Colour4F(0.f, 1.f, 0.f);
const Colour4F Colour4F::BLUE = Colour4F(0.f, 0.f, 1.f);
const Colour4F Colour4F::CYAN = Colour4F(0, 1.f, 1.f);
const Colour4F Colour4F::MAGENTA = Colour4F(1.f, 0.f, 1.f);
const Colour4F Colour4F::YELLOW = Colour4F(1.f, 1.f, 0.f);
const Colour4F Colour4F::BLACK = Colour4F(0.f, 0.f, 0.f);
const Colour4F Colour4F::WHITE = Colour4F(1.f, 1.f, 1.f);
const Colour4F Colour4F::TRANSLUCENT = Colour4F(0.f, 0.f, 0.f, 0.f);

Colour4F::Colour4F(float r, float g, float b, float a) 
	: red(r), green(g), blue(b), alpha(a)
{
}

Colour4F::Colour4F(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	red = float(r)/255.f;
	green = float(g)/255.f;
	blue = float(b)/255.f;
	alpha = float(a)/255.f;
}

string to_string(Colour4F c)
{
		return string("(") +
		to_string(c.red) + "|" +
		to_string(c.green) + "|" +
		to_string(c.blue) + "|" +
		to_string(c.alpha) + ")";
}