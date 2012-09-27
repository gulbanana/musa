#pragma once
#include <SFML/Graphics.hpp>
#include "CShapeGeometry.h"
#include "CPosition2D.h"
#include "ISystem.h"

class CollisionSystem : public ISystem
{
	float width;
	float height;

	sf::FloatRect getBounds(CShapeGeometry* geometry, CPosition2D* position);

public:
	CollisionSystem(float boundsX, float boundsY);
	std::vector<std::string> required_components() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
};

