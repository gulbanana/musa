#include "RenderSystem.h"
#include "Position2D.h"
#include "Drawable.h"
#include <array>
#include <iterator>
#include <typeinfo>
using namespace std;

vector<string> RenderSystem::required_components()
{
	array<string,2> compTypes = {typeid(Position2D).raw_name(), typeid(Drawable).raw_name()};
	return vector<string>(compTypes.begin(), compTypes.end());
}

void RenderSystem::frame()
{
	surface->clear();

	remove_if(begin(entities), end(entities), [](weak_ptr<IEntity> entity)
	{
		return entity.expired();
	});

	for_each(begin(entities), end(entities), [=](weak_ptr<IEntity> entity)
	{
		entity.lock();
			sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	sf::Text greeting("hello! hello", font);

	
	surface->draw(shape);
	surface->draw(greeting);
	});

}