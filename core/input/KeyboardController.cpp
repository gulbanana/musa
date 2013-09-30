#include <core/stdafx.h>
#include "KeyboardController.h"
using namespace std;

void KeyboardController::handle(SDL_Event& event)
{
    switch (event.type)
    {
		case SDL_KEYDOWN:
		{
			_keys.insert(event.key.keysym.sym);
            break;
		}

		case SDL_KEYUP:
		{
			_keys.erase(event.key.keysym.sym);
            break;
		}
    }
}

bool KeyboardController::get_key(SDLKey k)
{
	return _keys.find(k) != _keys.end();
}

int KeyboardController::get_axis(SDLKey negative, SDLKey positive)
{
    int result = 0;

	if (get_key(negative))
		result -= 1;
	if (get_key(positive))
		result += 1;

	return result;
}