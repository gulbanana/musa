#include <engine/core.h>
#include <engine/components.h>
#include "ResizingBouncer.h"
using namespace std;

ResizingBouncer::ResizingBouncer(std::shared_ptr<Camera2D> cam, int x, int y, int z) : Bouncer(x, y, z), _camera(cam)
{
}

bool ResizingBouncer::on_event(SDL_Event& event)
{
	if (event.type == SDL_VIDEORESIZE)
	{
		_width = (coord)event.resize.w;
		_height = (coord)event.resize.h;
		_camera->resize(_width, _height, _depth);

		for (auto weakentity : entities)
		{
			auto entity = weakentity.lock();

			if (entity->has_component<CVelocity>() && entity->get_component<CVelocity>()->vector != maths::origin)
			{
				auto position = entity->get_component<CPosition>();
				auto mesh = entity->get_component<CMesh>();
				auto box = mesh->geometry->bounds();

				position->location.x = min(position->location.x, _width - box.right());
				position->location.y = min(position->location.y, _width - box.top());
			}
		}
	}
	
	return false;
}