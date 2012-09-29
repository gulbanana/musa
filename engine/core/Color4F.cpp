#include "Color4F.h"

const Color4F Color4F::RED = Color4F(1.f, 0.f, 0.f);
const Color4F Color4F::GREEN = Color4F(0.f, 1.f, 0.f);
const Color4F Color4F::BLUE = Color4F(0.f, 0.f, 1.f);
const Color4F Color4F::CYAN = Color4F(0, 1.f, 1.f);
const Color4F Color4F::MAGENTA = Color4F(1.f, 1.f, 0.f);
const Color4F Color4F::YELLOW = Color4F(1.f, 0.f, 1.f);
const Color4F Color4F::BLACK = Color4F(0.f, 0.f, 0.f);
const Color4F Color4F::WHITE = Color4F(1.f, 1.f, 1.f);
const Color4F Color4F::TRANSLUCENT = Color4F(0.f, 0.f, 0.f, 0.f);

Color4F::Color4F(float r, float g, float b, float a) 
	: red(r), green(g), blue(b), alpha(a)
{
}

Color4F::Color4F(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	red = float(r)/255.f;
	green = float(g)/255.f;
	blue = float(b)/255.f;
	alpha = float(a)/255.f;
}