#pragma once
#include <core/framework.h>
#include <tile/types.h>
#include <core/text/FontManager.h>
#include <SDL_video.h>
#include "IBlitter.h"

#define MIN_FONT 8.f
#define DEFAULT_FONT 24.f
#define MAX_FONT 32.f

struct GridDimensions
{
    int x;
    int y;
};

class GLBlitSystem : public Identified<GLBlitSystem, ISystem>, public IBlitter
{
private:
	SDL_Window* _window;
    SDL_GLContext _context;

    grid _tram;
	FontManager* _fonts;

	int _width;
	int _height;
	float _font_size;
    bool _is_fullscreen;

	std::vector<ISystem::ID> required_systems() const override;
	void on_frame() override;
	bool on_event(SDL_Event&) override;

	void resizeGrid(RoundingMode mode);

public:
	GLBlitSystem(SDL_Window* window);
	~GLBlitSystem();

	grid* get_tram() override;
};

