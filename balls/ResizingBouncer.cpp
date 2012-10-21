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

		((OrthographicCamera*)_camera->get_component<CCamera>()->view)->range = box6(maths::origin, _width, _height, _depth);
		_camera->get_component<CTransform>()->translate = point(_width/2, _height/2, _depth);

		for (auto weakentity : entities)
		{
			auto entity = weakentity.lock();

			if (entity->has_component<CVelocity>() && entity->get_component<CVelocity>()->vector != maths::origin)
			{
				auto position = entity->get_component<CTransform>();
				auto mesh = entity->get_component<CModel>();
				auto box = mesh->geometry->bounds();

				position->translate.x = min(position->translate.x, _width - box.right());
				position->translate.y = min(position->translate.y, _width - box.top());
			}
		}
	}
	
	return false;
}