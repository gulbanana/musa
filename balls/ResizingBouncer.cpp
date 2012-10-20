#include <engine/core.h>
#include <engine/components.h>
#include "ResizingBouncer.h"
using namespace std;

ResizingBouncer::ResizingBouncer(std::shared_ptr<IEntity> camera, int x, int y, int z) : Bouncer(x, y, z), _camera(camera)
{
}

bool ResizingBouncer::on_event(SDL_Event& event)
{
	if (event.type == SDL_VIDEORESIZE)
	{
		_width = (coord)event.resize.w;
		_height = (coord)event.resize.h;

		((OrthographicCamera*)_camera->get_component<CTransform>()->view)->range = box6(maths::origin, _width, _height, _depth);
		_camera->get_component<CPosition>()->location = point(_width/2, _height/2, _depth);

		for (auto weakentity : entities)
		{
			auto entity = weakentity.lock();

			if (entity->has_component<CVelocity>() && entity->get_component<CVelocity>()->vector != maths::origin)
			{
				auto position = entity->get_component<CPosition>();
				auto mesh = entity->get_component<CModel>();
				auto box = mesh->geometry->bounds();

				position->location.x = min(position->location.x, _width - box.right());
				position->location.y = min(position->location.y, _width - box.top());
			}
		}
	}
	
	return false;
}