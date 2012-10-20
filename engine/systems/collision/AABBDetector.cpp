#include <engine/core.h>
#include <engine/components.h>
#include "AABBDetector.h"

bool AABBDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	auto sourceMesh = source->get_component<CModel>();
	auto sourcePosition = source->get_component<CPosition>();

	auto targetMesh = target->get_component<CModel>();
	auto targetPosition = target->get_component<CPosition>();

	box6 sourceBounds = sourceMesh->geometry->bounds() + sourcePosition->location;
	box6 targetBounds = targetMesh->geometry->bounds() + targetPosition->location;

	if (sourceBounds.intersects(targetBounds))
	{
		return true;
	}

	return false;
}