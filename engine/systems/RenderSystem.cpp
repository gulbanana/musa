#include <array>
#include <iterator>
#include <typeinfo>
#include "../components.h"
#include "RenderSystem.h"
using namespace std;

vector<IComponent::ID> ShapeRenderSystem::required_components()
{
	array<IComponent::ID,2> compTypes = {IComponent::ID::Position2D, IComponent::ID::ShapeGeometry};
	return vector<IComponent::ID>(compTypes.begin(), compTypes.end());
}

ShapeRenderSystem::ShapeRenderSystem(sf::Font f, sf::RenderTarget* s) : font(f), surface(s) 
{
	reusableCircle = sf::CircleShape();
	reusableRectangle = sf::RectangleShape();
	reusableTextRun = sf::Text("", font);
	reusableTextRun.setColor(sf::Color::Black);
}

void ShapeRenderSystem::on_frame()
{
	surface->clear();
}

void ShapeRenderSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition2D>();
	auto geometry = entity->get_component<CShapeGeometry>();

	auto entityTranslation = sf::Transform();
	entityTranslation.translate(position->current.x - geometry->radius, position->current.y - geometry->radius);
		
	sf::Shape* shape;
	switch (geometry->shape)
	{
		case Polygon::CIRCLE:
			reusableCircle.setRadius(geometry->radius);
			shape = &reusableCircle;
			break;

		case Polygon::SQUARE:
			reusableRectangle.setSize(sf::Vector2f(geometry->radius*2, geometry->radius*2));
			shape = &reusableRectangle;
			break;
		
		case Polygon::TRIANGLE:
		default:
			throw exception("can't render this");
			break;
	}

	shape->setFillColor(geometry->color);
	surface->draw(*shape, sf::RenderStates(entityTranslation));

	if (entity->has_component<CLabel>())
	{
		auto label = entity->get_component<CLabel>();

		entityTranslation.translate(geometry->radius - 25, geometry->radius - 20);
		reusableTextRun.setString(label->text);
		surface->draw(reusableTextRun, sf::RenderStates(entityTranslation));
	}
}