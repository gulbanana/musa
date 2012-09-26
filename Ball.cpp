#include "Ball.h"
#include "Position2D.h"
#include "Drawable.h"
#include <memory>
using namespace std;

Ball::Ball(sf::Color color, float offset)
{
	components.push_back(unique_ptr<IComponent>((IComponent*)new Position2D(offset, offset)));
	components.push_back(unique_ptr<IComponent>((IComponent*)new Drawable(Drawable::Shape::CIRCLE, color, "hello")));
}
