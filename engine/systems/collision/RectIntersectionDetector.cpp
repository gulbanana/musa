#include <engine/components.h>
#include "RectIntersectionDetector.h"

bool RectIntersectionDetector::collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target)
{
	/*auto sourceGeometry = source->get_component<CGeometry2D>();
	auto sourcePosition = source->get_component<CPosition2D>();
	

	auto targetGeometry = target->get_component<CGeometry2D>();
	auto targetPosition = target->get_component<CPosition2D>();

	sf::FloatRect sourceRect = getBounds(sourceGeometry, sourcePosition);
	sf::FloatRect targetRect = getBounds(targetGeometry, targetPosition);

	if (sourceRect.intersects(targetRect))
	{
		auto sourceVelocity = source->get_component<CVelocity2D>();
		auto xDiff = abs(targetPosition->current.x - sourcePosition->current.x);
		auto yDiff = abs(targetPosition->current.y - sourcePosition->current.y);

		if (xDiff > yDiff)
			sourceVelocity->vector.x *= -1;
		else if (yDiff > xDiff)
			sourceVelocity->vector.y *= -1;
		else
		{
			sourceVelocity->vector.x *= -1;
			sourceVelocity->vector.y *= -1;
		}
	}*/

	return false;
}