#include <engine/core.h>
#include "MicrosoftPlatform.h"
#include "Windows.h"
using namespace std;

MicrosoftPlatform::MicrosoftPlatform() : SDLPlatformBase()
{
    set_environment_variable("SDL_VIDEO_WINDOW_POS", "center");
	_tick_offset = GetTickCount();
}

MicrosoftPlatform::~MicrosoftPlatform()
{
	
}

void MicrosoftPlatform::print(string output)
{
    OutputDebugStringA(output.c_str());
}

void MicrosoftPlatform::set_environment_variable(string variable, string value)
{
	_putenv_s(variable.c_str(), value.c_str());
}

string MicrosoftPlatform::get_environment_variable(string variable)
{
	char* c_val;

	_dupenv_s(&c_val, nullptr, variable.c_str());

	string cpp_val(c_val);
	
	free(c_val);
	return cpp_val;
}

milliseconds MicrosoftPlatform::get_ticks()
{
    return GetTickCount() - _tick_offset;
}

void MicrosoftPlatform::sleep_ticks(milliseconds ttw)
{
	Sleep(ttw);
}
