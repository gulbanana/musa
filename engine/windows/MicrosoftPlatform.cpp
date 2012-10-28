#include <engine/core.h>
#include "Windows.h"
using namespace std;

void platform::print(string output)
{
	OutputDebugStringA(output.c_str());
}

void platform::setenv(string variable, string value)
{
#pragma error "implement putenv() for windows"
}