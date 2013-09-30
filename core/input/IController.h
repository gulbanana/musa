#pragma once
#include <SDL_events.h>

//a "controller" handles some events and provides state for control systems
class IController
{
public:
    virtual void handle(SDL_Event& event) = 0;
};