#include <core/stdafx.h>
#include "CapturedMouseController.h"
using namespace std;

CapturedMouseController::CapturedMouseController()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void CapturedMouseController::handle(SDL_Event& event)
{
    /*switch (event.type)
    {
    	case SDL_MOUSEMOTION:
        {
			//XXX change this to an init message
            //XXX2 what does that mean? message as in "sent by the engine to the system?"
			if (!_inited)
			{
				_inited = true;
                
				SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
				SDL_WarpMouse(500, 500);
				SDL_WM_GrabInput(SDL_GRAB_ON);
				SDL_EnableKeyRepeat(0, 0);	//disable
				SDL_ShowCursor(SDL_DISABLE);
				SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);

                disabled = true;
				return;
			}
            
        			
            //move the cursor somewhere it can't bother us
			SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
			SDL_WarpMouse(500, 500);
			SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
            disabled = false;
        }
    }*/
}