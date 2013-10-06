#include "core/stdafx.h"
#include "GLEngineBase.h"
using namespace std;

GLEngineBase::GLEngineBase() : _settings(nullptr), _state(nullptr), _surface(nullptr) {}

GLEngineBase::~GLEngineBase()
{
    if (_surface != nullptr) SDL_DestroyWindow(_surface);
}

void GLEngineBase::init(unique_ptr<GameSettings> settings, GameState* state)
{
    _settings = move(settings);
    _state = state;

    _surface = SDL_CreateWindow(_settings->window_title.c_str(), 
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                _settings->initial_width, _settings->initial_height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (_surface == 0) throw new runtime_error("GLEngineBase: failed to create SDL window");
}