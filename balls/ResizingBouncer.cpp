#include "stdafx.h"
#include <mesh/components.h>
#include "ResizingBouncer.h"
#include <windows.h>
using namespace std;

ResizingBouncer::ResizingBouncer(std::shared_ptr<IEntity> camera, int x, int y, int z) : Bouncer(x, y, z), _camera(camera)
{
    do_resize(x, y);
}

bool ResizingBouncer::on_event(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_WINDOWEVENT:
        {
            switch (event.window.event)
            {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                    do_resize(event.window.data1, event.window.data2);
                    break;
                }
            }
            break;
        }
    }

    return false;
}

void ResizingBouncer::do_resize(int w, int h)
{
    _width = (coord)w;
    _height = (coord)h;

    ((OrthographicCamera*)_camera->get_component<CRenderable>()->geometry)->range = box6(constants::origin, _width, _height, _depth);
	_camera->get_component<CTransform>()->translate = point(_width/2, _height/2, _depth);

	for (auto weakentity : entities)
	{
		auto entity = weakentity.lock();

		if (entity->has_component<CVelocity>() && entity->get_component<CVelocity>()->vector != constants::origin)
		{
			auto position = entity->get_component<CTransform>();
			auto mesh = entity->get_component<CRenderable>();
			auto box = mesh->geometry->bounds();

			position->translate.x = min(position->translate.x, _width - box.right());
			position->translate.y = min(position->translate.y, _width - box.top());
		}
	}
}