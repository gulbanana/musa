#include <engine/components.h>
#include "AABBDetector.h"

bool AABBDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	auto sourceMesh = source->get_component<CMesh>();
	auto sourcePosition = source->get_component<CPosition>();

	auto targetMesh = target->get_component<CMesh>();
	auto targetPosition = target->get_component<CPosition>();

	Box6<coord> sourceBounds = sourceMesh->geometry->bounds() + sourcePosition->location;
	Box6<coord> targetBounds = targetMesh->geometry->bounds() + targetPosition->location;

	if (sourceBounds.intersects(targetBounds))
	{
		return true;
	}

	return false;
}