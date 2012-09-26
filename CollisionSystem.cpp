#include "CollisionSystem.h"
#include "CPosition2D.h"
#include "CShapeGeometry.h"
#include "CCollision.h"
#include <array>
#include <iterator>
#include <typeinfo>
using namespace std;

vector<string> CollisionSystem::required_components()
{
	array<string,3> compTypes = {"Position2D", "ShapeGeometry", "Collision"};
	return vector<string>(compTypes.begin(), compTypes.end());
}

CollisionSystem::CollisionSystem(float boundsX, float boundsY)
{
	width = boundsX;
	height = boundsY;
}

void CollisionSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = static_cast<CPosition2D*>(entity->get_component("Position2D"));
	auto geometry = static_cast<CShapeGeometry*>(entity->get_component("ShapeGeometry"));
	auto collision = static_cast<CCollision*>(entity->get_component("Collision"));

	collision->collidedX = false;
	collision->collidedY = false;

	bool outOfBoundsX = position->x <= 0.f || (position->x + geometry->radius*2) >= width;
	bool outOfBoundsY = position->y <= 0.f || (position->y + geometry->radius*2) >= height;

	if (outOfBoundsX) collision->collidedX = true;
	if (outOfBoundsY) collision->collidedY = true;
	
	sf::FloatRect sourceRect = getBounds(geometry, position);
	for_each(entities.begin(), entities.end(), [&, sourceRect, collision, position](weak_ptr<IEntity> potentialCollision)
	{
		auto target = potentialCollision.lock();
		if (target.get() == entity.get())
			return;

		auto targetGeometry = static_cast<CShapeGeometry*>(target->get_component("ShapeGeometry"));
		auto targetPosition = static_cast<CPosition2D*>(target->get_component("Position2D"));
		sf::FloatRect targetRect = getBounds(targetGeometry, targetPosition);

		if (sourceRect.intersects(targetRect))
		{
			auto xDiff = abs(targetPosition->x - position->x);
			auto yDiff = abs(targetPosition->y - position->y);

			if (xDiff > yDiff)
				collision->collidedX = true;
			else if (yDiff > xDiff)
				collision->collidedY = true;
			else
			{
				collision->collidedX = true;
				collision->collidedY = true;
			}
			return;
		}
	});
}

sf::FloatRect CollisionSystem::getBounds(CShapeGeometry* geometry, CPosition2D* position)
{
	return sf::Rect<float>(
		position->x - geometry->radius, 
		position->y - geometry->radius, 
		geometry->radius * 2, 
		geometry->radius * 2
	);
}