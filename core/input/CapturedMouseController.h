#pragma once
#include "IController.h"

class CapturedMouseController : IController
{
public:
    CapturedMouseController();
    void handle(SDL_Event& event) override;
};

