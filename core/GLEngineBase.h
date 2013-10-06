#pragma once
#include "IGameEngine.h"

class GLEngineBase : public IGameEngine
{
protected:
    std::unique_ptr<GameSettings> _settings;
    GameState* _state;
    SDL_Window* _surface;

    GLEngineBase();
    virtual ~GLEngineBase();

    void init(std::unique_ptr<GameSettings> settings, GameState* state) override;
};

