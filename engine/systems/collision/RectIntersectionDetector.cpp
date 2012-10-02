#include <engine/components.h>
#include "RectIntersectionDetector.h"

bool RectIntersectionDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	auto sourceMesh = source->get_component<CMesh>();
	auto sourcePosition = source->get_component<CPosition>();

	auto targetMesh = target->get_component<CMesh>();
	auto targetPosition = target->get_component<CPosition>();

	Rect4F sourceBounds = sourceMesh->geometry->bounds().slice() + sourcePosition->location.get2D();
	Rect4F targetBounds = targetMesh->geometry->bounds().slice() + targetPosition->location.get2D();

	if (sourceBounds.intersects(targetBounds))
	{
		return true;
	}

	return false;
}