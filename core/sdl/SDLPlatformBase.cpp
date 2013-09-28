#include <core/stdafx.h>
#include <SDL.h>
#include "SDLPlatformBase.h"
using namespace std;

SDLPlatformBase::SDLPlatformBase()
{
	Uint32 flags = SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE;
    
    int rc = SDL_Init(flags);
    if (rc != 0)
    {
        SDL_Error(SDL_LASTERROR);
        throw runtime_error("SDL_Init failed");
    }
    
    SDL_EnableUNICODE(1);   //for guichan
}

SDLPlatformBase::~SDLPlatformBase()
{
    SDL_Quit();
}

string SDLPlatformBase::get_window_title()
{
    char* title;
	SDL_WM_GetCaption(&title, nullptr);
    
    return string(title);
}

void SDLPlatformBase::set_window_title(string title)
{
	SDL_WM_SetCaption(title.c_str(), nullptr);
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