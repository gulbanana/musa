#pragma once
#include "Bouncer.h"

class ResizingBouncer : public Bouncer
{
private:
	std::shared_ptr<IEntity> _camera;

	virtual bool on_event(SDL_Event&) override;

public:
	ResizingBouncer(std::shared_ptr<IEntity> camera, int x, int y, int z);
};

