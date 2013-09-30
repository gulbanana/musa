#include <core/stdafx.h>
#include "MouseController.h"
using namespace std;

MouseController::MouseController() : _inited(false), disabled(false)
{
}

void MouseController::handle(SDL_Event& event)
{
    switch (event.type)
    {
    	case SDL_MOUSEMOTION:
        {
			//XXX change this to an init message
            //XXX2 what does that mean?
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
    }
}