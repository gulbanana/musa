#include <engine/core.h>
#include "Windows.h"
using namespace std;

MicrosoftPlatform::MicrosoftPlatform() : SDLPlatformBase()
{
    set_environment_variable("SDL_VIDEO_WINDOW_POS", "center");
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

}

string MicrosoftPlatform::get_environment_variable(string cpp_var)
{

}