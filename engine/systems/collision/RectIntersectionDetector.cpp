#include <engine/core.h>
#include <engine/components.h>
#include "RectIntersectionDetector.h"

bool RectIntersectionDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	auto sourceMesh = source->get_component<CMesh>();
	auto sourcePosition = source->get_component<CPosition>();

	auto targetMesh = target->get_component<CMesh>();
	auto targetPosition = target->get_component<CPosition>();

	Rect4<coord> sourceBounds = Rect4<coord>(sourceMesh->geometry->bounds()) + Vec2<coord>(sourcePosition->location);
	Rect4<coord> targetBounds = Rect4<coord>(targetMesh->geometry->bounds()) + Vec2<coord>(targetPosition->location);

	if (sourceBounds.intersects(targetBounds))
	{
		return true;
	}

	return false;
}