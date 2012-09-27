#include "RenderSystem.h"
#include "CPosition2D.h"
#include "CShapeGeometry.h"
#include "CLabel.h"
#include "CCollision.h"
#include <array>
#include <iterator>
#include <typeinfo>
using namespace std;

vector<string> RenderSystem::required_components()
{
	array<string,3> compTypes = {"Position2D", "ShapeGeometry", "Label"};
	return vector<string>(compTypes.begin(), compTypes.end());
}

RenderSystem::RenderSystem(sf::RenderTarget* s) : surface(s)
{
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
}

void RenderSystem::on_frame()
{
	surface->clear();
}

void RenderSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = static_cast<CPosition2D*>(entity->get_component("Position2D"));
	auto geometry = static_cast<CShapeGeometry*>(entity->get_component("ShapeGeometry"));
	auto label = static_cast<CLabel*>(entity->get_component("Label"));

	auto entityTranslation = sf::Transform();
	entityTranslation.translate(position->x, position->y);
		
	sf::Shape* shape;
	sf::CircleShape circle(geometry->radius);
	sf::RectangleShape square(sf::Vector2f(geometry->radius*2, geometry->radius*2));
	switch (geometry->shape)
	{
		case CShapeGeometry::Shape::CIRCLE:
			shape = &circle;
			break;
		case CShapeGeometry::Shape::SQUARE:
			shape = &square;
			break;
	}

	shape->setFillColor(geometry->color);
	surface->draw(*shape, sf::RenderStates(entityTranslation));

	sf::Text greeting(label->text, font);
	greeting.setColor(sf::Color::Black);
	entityTranslation.translate(geometry->radius-25, geometry->radius-20);
	surface->draw(greeting, sf::RenderStates(entityTranslation));
}