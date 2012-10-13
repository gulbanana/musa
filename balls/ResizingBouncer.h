#pragma once
#include "Bouncer.h"
#include <engine/entities.h>

class ResizingBouncer : public Bouncer
{
private:
	std::shared_ptr<Camera2D> _camera;

	virtual bool on_event(SDL_Event&) override;

public:
	ResizingBouncer(std::shared_ptr<Camera2D>, int x, int y, int z);
};

