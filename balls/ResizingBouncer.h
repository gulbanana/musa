#pragma once
#include "Bouncer.h"

class ResizingBouncer : public Bouncer
{
private:
	std::shared_ptr<IEntity> _camera;

    void do_resize(int w, int h);

public:
    std::string description() const final;

	ResizingBouncer(std::shared_ptr<IEntity> camera, int x, int y, int z);

    virtual bool on_event(SDL_Event&) override;
};

