#include <engine/core.h>
#include <engine/components.h>
#include "RectIntersectionDetector.h"

bool RectIntersectionDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	auto sourceMesh = source->get_component<CModel>();
	auto sourcePosition = source->get_component<CPosition>();

	auto targetMesh = target->get_component<CModel>();
	auto targetPosition = target->get_component<CPosition>();

	rect4 sourceBounds = rect4(sourceMesh->geometry->bounds()) + glm::vec2(sourcePosition->location.x, sourcePosition->location.y);
	rect4 targetBounds = rect4(targetMesh->geometry->bounds()) + glm::vec2(targetPosition->location.x, targetPosition->location.y);

	if (sourceBounds.intersects(targetBounds))
	{
		return true;
	}

	return false;
}