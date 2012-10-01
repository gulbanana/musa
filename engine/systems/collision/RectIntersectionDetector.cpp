#include <engine/components.h>
#include "RectIntersectionDetector.h"

bool RectIntersectionDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	auto sourceExtents = source->get_component<CExtents<Rect4F>>();
	auto sourcePosition = source->get_component<CPosition>();

	auto targetExtents = target->get_component<CExtents<Rect4F>>();
	auto targetPosition = target->get_component<CPosition>();

	Rect4F sourceBounds = sourceExtents->bounds->accept(&_bounder) + sourcePosition->location.get2D();
	Rect4F targetBounds = targetExtents->bounds->accept(&_bounder) + targetPosition->location.get2D();

	if (sourceBounds.intersects(targetBounds))
	{
		return true;
	}

	return false;
}