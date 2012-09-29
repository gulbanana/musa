#include <memory>
#include <engine/World.h>
#include <random>
#include "Obstacle.h"
#include "Backdrop.h"
#include "Ball.h"
#include "LargeBall.h"

using namespace std;

extern "C"
int main(int argc, char *argv[])
{
	auto ballgame = World("balls!");

	//immobiles
	ballgame.add_entity(make_shared<Obstacle>(Color4F::WHITE, Vector2F(275.f, 300.f)));
	ballgame.add_entity(make_shared<Backdrop>(Color4F::WHITE, Vector2F(525.f, 300.f), 10.f));

	//fixed balls
	ballgame.add_entity(make_shared<LargeBall>(Color4F::CYAN, Vector2F(100.f, 100.f), Vector2F(100.f, -100.f)));
	ballgame.add_entity(make_shared<LargeBall>(Color4F::MAGENTA, Vector2F(580.f, 300.f), Vector2F(100.f, 100.f)));
	ballgame.add_entity(make_shared<LargeBall>(Color4F::YELLOW, Vector2F(260.f, 500.f), Vector2F(-100.f, 100.f)));
	
	//random balls
	for (int i = 0; i < 25; i++) {
		ballgame.add_entity(
			make_shared<Ball>(
				Color4F(0.f, 1.f, 0.f, 0.75f), 
				Vector2F(
					((float)rand() / (float)RAND_MAX) * 800, 
					((float)rand() / (float)RAND_MAX) * 600
				),
				Vector2F(
					(((float)rand() / (float)RAND_MAX) - 0.5f) * 300,
					(((float)rand() / (float)RAND_MAX) - 0.5f) * 300
				)
			)
		);
	}

	ballgame.play();

	return 0;
}
