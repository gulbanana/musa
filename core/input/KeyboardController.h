#pragma once
#include <SDL_keyboard.h>
#include "IController.h"

class KeyboardController : IController
{
private:
    std::set<SDL_Keycode> _keys;

public:
    void handle(SDL_Event&) override;
   	bool get_key(SDL_Keycode);
    int get_axis(SDL_Keycode negative, SDL_Keycode positive);
};

