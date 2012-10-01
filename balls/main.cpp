#include <memory>
#include <random>
#include <engine/World.h>
#include <engine/misc.h>
#include "Obstacle.h"
#include "Ball.h"
#include "BallBouncer.h"
using namespace std;

extern "C"
int main(int argc, char *argv[])
{
	auto ballgame = World("balls!");

	//special logic system
	ballgame.add_system(make_unique<BallBouncer>(800, 600));

	//immobiles
	ballgame.add_entity(make_unique<Obstacle>(Color4F::WHITE, Vector2F(275.f, 300.f), Vector3F(0.f, 0.f, 0.f)));
	ballgame.add_entity(make_unique<Obstacle>(Color4F::WHITE, Vector2F(525.f, 300.f), Vector3F(45.f, 90.f, 0.f), false));

	//fixed balls
	ballgame.add_entity(make_unique<Ball>(25.f, Color4F::CYAN, Vector2F(100.f, 100.f), Vector2F(100.f, -100.f), true));
	ballgame.add_entity(make_unique<Ball>(25.f, Color4F::MAGENTA, Vector2F(580.f, 300.f), Vector2F(100.f, 100.f), true));
	ballgame.add_entity(make_unique<Ball>(25.f, Color4F::YELLOW, Vector2F(260.f, 500.f), Vector2F(-100.f, 100.f), true));
	
	//random balls
	for (int i = 0; i < 30; i++) {
		ballgame.add_entity(
			make_unique<Ball>(
				10.f,
				Color4F(0.f, 1.f, 0.f, 0.75f), 
				Vector2F(
					((float)rand() / (float)RAND_MAX) * 800, 
					((float)rand() / (float)RAND_MAX) * 600
				),
				Vector2F(
					(((float)rand() / (float)RAND_MAX) - 0.5f) * 400,
					(((float)rand() / (float)RAND_MAX) - 0.5f) * 400
				),
				true
			)
		);
	}

	ballgame.play();

	return 0;
}
