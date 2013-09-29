#pragma once
#include <core/framework.h>
#include <tile/types.h>
#include <tile/font/fontstash.h>
#include <SDL_video.h>
#include "IBlitter.h"

class GLBlitSystem : public Identified<ISystem,SYS::Render,ThreadedSystemBase>, public IBlitter
{
private:
	grid _tram;
	SDL_Surface* _surface;
	sth_stash* _fonts;

private:
	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;
	bool on_event(SDL_Event&) override;

public:
	GLBlitSystem(unsigned int pixelWidth, unsigned int pixelHeight);
	~GLBlitSystem();

	grid* get_tram() override;
};

