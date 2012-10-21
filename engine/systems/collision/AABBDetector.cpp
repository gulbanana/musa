#include <engine/core.h>
#include <engine/components.h>
#include "AABBDetector.h"

bool AABBDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	auto sourceMesh = source->get_component<CModel>();
	auto sourcePosition = source->get_component<CTransform>();

	auto targetMesh = target->get_component<CModel>();
	auto targetPosition = target->get_component<CTransform>();

	box6 sourceBounds = sourceMesh->geometry->bounds() + sourcePosition->translate;
	box6 targetBounds = targetMesh->geometry->bounds() + targetPosition->translate;

	if (sourceBounds.intersects(targetBounds))
	{
		return true;
	}

	return false;
}