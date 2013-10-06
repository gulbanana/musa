#include <core/stdafx.h>
#include <SDL.h>
#include "SDLPlatformBase.h"
using namespace std;

SDLPlatformBase::SDLPlatformBase()
{
	int rc = SDL_Init(SDL_INIT_EVERYTHING);
    if (rc != 0)
    {
        SDL_Error(SDL_LASTERROR);
        throw runtime_error("SDL_Init failed");
    }
}

SDLPlatformBase::~SDLPlatformBase()
{
    SDL_Quit();
}

void SDLPlatformBase::quit()
{
    /* Post a SDL_QUIT event */
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
}

milliseconds SDLPlatformBase::get_ticks()
{
    return SDL_GetTicks();
}

void SDLPlatformBase::sleep_ticks(milliseconds atLeast)
{
    SDL_Delay(atLeast);
}