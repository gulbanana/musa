#include "GreenBall.h"
#include "Position2D.h"
#include "Drawable.h"
#include <memory>
using namespace std;

GreenBall::GreenBall()
{
	components.push_back(shared_ptr<IComponent>((IComponent*)new Position2D(0.0, 0.0)));
	components.push_back(shared_ptr<IComponent>((IComponent*)new Drawable(Drawable::Shape::CIRCLE, sf::Color::Green)));
}


GreenBall::~GreenBall()
{
}
