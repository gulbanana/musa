#pragma once
#include <core/framework.h>
#include <tile/types.h>
#include <core/text/FontManager.h>
#include <SDL_video.h>
#include "IBlitter.h"

class GLBlitSystem : public Identified<GLBlitSystem, ISystem, ThreadedSystemBase>, public IBlitter
{
private:
	SDL_Window* _window;
    SDL_GLContext _context;

    grid _tram;
	FontManager* _fonts;

	int _width;
	int _height;
	float _font_size;

	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;
	bool on_event(SDL_Event&) override;

	void resize();

public:
	GLBlitSystem(SDL_Window* window);
	~GLBlitSystem();

	grid* get_tram() override;
};

