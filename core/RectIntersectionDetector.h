#pragma once
#include <SFML/Graphics.hpp>
#include "ICollisionDetector.h"

class RectIntersectionDetector : public ICollisionDetector
{
	sf::FloatRect getBounds(CShapeGeometry* geometry, CPosition2D* position);
public:
	bool collide(std::shared_ptr<IEntity> source, std::shared_ptr<IEntity> target) override;
};

