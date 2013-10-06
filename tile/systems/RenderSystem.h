#pragma once
#include <core/framework.h>
#include <core/GameState.h>
#include "IBlitter.h"

class RenderSystem : public Identified<RenderSystem, ISystem, EntityManagingSystemBase>
{
private:
	GameState* _state;
	IBlitter* _blitter;
    grid* _tram;

    int _cam_centre_x;
    int _cam_centre_y;
    int _cam_z;

    int _cam_top;
    int _cam_bottom;
    int _cam_left;
    int _cam_right;

    char _fill;

    bool within_camera_bounds(point);

private:
	std::vector<ISystem::ID> required_systems() const override;
    std::vector<IComponent::ID> required_components() const override;
    void on_frame_start() override;
    void on_frame_entity(std::shared_ptr<IEntity>) override;
    bool on_event(SDL_Event&) override;

public:
	RenderSystem(GameState*, IBlitter*);
	~RenderSystem();
};

