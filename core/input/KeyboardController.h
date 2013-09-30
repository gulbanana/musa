#pragma once
#include "IController.h"

class KeyboardController : IController
{
private:
    std::set<SDLKey> _keys;

public:
    void handle(SDL_Event&) override;
   	bool get_key(SDLKey);
    int get_axis(SDLKey negative, SDLKey positive);
};

