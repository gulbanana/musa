#pragma once
#include "IController.h"

class MouseController : IController
{
    bool _inited;

public:
    bool disabled;

    MouseController();
    void handle(SDL_Event& event) override;
};

