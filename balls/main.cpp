#include <memory>
#include <core/World.h>
#include "Obstacle.h"
#include "Backdrop.h"
#include "Ball.h"

using namespace std;

int main()
{
	auto ballgame = World();

	ballgame.add_entity(make_shared<Obstacle>(sf::Color::White, 200.f, 300.f));
	ballgame.add_entity(make_shared<Backdrop>(sf::Color::White, 400.f, 300.f));

	ballgame.add_entity(make_shared<Ball>(sf::Color::Cyan, 100.f, 100.f));
	ballgame.add_entity(make_shared<Ball>(sf::Color::Magenta, 200.f, 400.f));
	ballgame.add_entity(make_shared<Ball>(sf::Color::Yellow, 300.f, 200.f));

	ballgame.play();

	return 0;
}
