#include <memory>
#include <core/World.h>
#include "Obstacle.h"
#include "Backdrop.h"
#include "Ball.h"

using namespace std;

int main()
{
	auto ballgame = World("balls.exe");

	//immobiles
	ballgame.add_entity(make_shared<Obstacle>(Color4F::WHITE, Vector2F(250.f, 350.f)));
	ballgame.add_entity(make_shared<Obstacle>(Color4F::WHITE, Vector2F(450.f, 350.f)));

	//fixed balls
	ballgame.add_entity(make_shared<Ball>(Color4F::CYAN, Vector2F(100.f, 100.f), Vector2F(2.f, 2.f)));
	ballgame.add_entity(make_shared<Ball>(Color4F::MAGENTA, Vector2F(180.f, 300.f), Vector2F(2.f, 2.f)));
	ballgame.add_entity(make_shared<Ball>(Color4F::YELLOW, Vector2F(260.f, 500.f), Vector2F(2.f, 2.f)));

	//random balls
	for (int i = 0; i < 25; i++)
		ballgame.add_entity(make_shared<Ball>(Color4F::GREEN));

	ballgame.play();

	return 0;
}
