#pragma once
#include <core/framework.h>
#include <tile/types.h>
#include <SDL_video.h>

class BlitSystem : public Identified<ISystem,SYS::Render,ThreadedSystemBase>
{
private:
	SDL_Surface* _surface;
	grid _tram;

private:
	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;
	bool on_event(SDL_Event&) override;

public:
	BlitSystem(unsigned int pixelWidth, unsigned int pixelHeight);
	~BlitSystem();
};

