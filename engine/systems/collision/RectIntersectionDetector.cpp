#include <engine/core.h>
#include <engine/components.h>
#include "RectIntersectionDetector.h"

bool RectIntersectionDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	auto sourceMesh = source->get_component<CRenderable>();
	auto sourcePosition = source->get_component<CTransform>();

	auto targetMesh = target->get_component<CRenderable>();
	auto targetPosition = target->get_component<CTransform>();

	rect4 sourceBounds = rect4(sourceMesh->geometry->bounds()) + glm::vec2(sourcePosition->translate.x, sourcePosition->translate.y);
	rect4 targetBounds = rect4(targetMesh->geometry->bounds()) + glm::vec2(targetPosition->translate.x, targetPosition->translate.y);

	if (sourceBounds.intersects(targetBounds))
	{
		return true;
	}

	return false;
}