#include <tile/stdafx.h>
#include <tile/components.h>
#include "RenderSystem.h"
#include "MotionSystem.h"
#include <algorithm>
using namespace std;

string RenderSystem::description() const
{
    return "2D renderer";
}

vector<ISystem::ID> RenderSystem::required_systems() const
{
	return ISystem::require<MotionSystem>();
}

std::vector<IComponent::ID> RenderSystem::required_components() const
{
    return IComponent::require<CDraw, CTransform>();
}

RenderSystem::RenderSystem(GameState* state, IBlitter* blitter) : _state(state), _blitter(blitter)
{
    _cam_centre_x = 0;
    _cam_centre_y = 0;
    _cam_z = 0;

    _fill = '.';
}

RenderSystem::~RenderSystem() {}

void RenderSystem::on_frame_start()
{
	_tram = _blitter->get_tram();

	_tram->fill(_fill);

    _cam_left = _cam_centre_x - _tram->width/2;
    _cam_bottom = _cam_centre_y - _tram->height/2;
    _cam_right = _cam_left + _tram->width;
    _cam_top = _cam_bottom + _tram->height;
}

void RenderSystem::on_frame_entity(std::shared_ptr<IEntity> e)
{
    auto transform = e->get_component<CTransform>();
    
    if (!within_camera_bounds(transform->translate)) return;

    auto drawable = e->get_component<CDraw>();
    _tram->draw(drawable->layout, transform->translate.x - _cam_left, transform->translate.y - _cam_bottom);
}

bool RenderSystem::within_camera_bounds(point p)
{
    return p.x >= _cam_left && p.y >= _cam_bottom &&
           p.x <= _cam_right && p.y <= _cam_top;
}

bool RenderSystem::on_event(SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_TEXTINPUT:
        {
            _fill = event.text.text[0];
            break;
        }
    }

    return false;
}