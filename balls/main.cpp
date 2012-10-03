#include <memory>
#include <random>
#include <ctime>
#include <engine/World.h>
#include <engine/misc.h>
#include "Obstacle.h"
#include "Ball.h"
#include "BallBouncer.h"
using namespace std;

#define LOC(x, y) Vec2<coord>((coord)(x), (coord)(y))
#define VEL(x, y) Vec2<coord>((coord)(x), (coord)(y))
#define ROT(x, y, z) Vec3<degrees>((degrees)(x), (degrees)(y), (degrees)(z))

void setup_world(World&);

extern "C"
int main(int argc, char *argv[])
{
	auto game = World("balls!");
	setup_world(game);
	game.play();

	return 0;
}

void setup_world(World& ballgame)
{
	//special logic system
	ballgame.add_system(make_unique<BallBouncer>(800, 600));

	//immobiles
	ballgame.add_entity(make_unique<Obstacle>(Color4F::WHITE, LOC(275, 300), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Obstacle>(Color4F::WHITE, LOC(525, 300), ROT(45,90,0), false));

	//fixed balls
	ballgame.add_entity(make_unique<Ball>((coord)25, Color4F::CYAN, LOC(100,100), VEL(100,-100), true));
	ballgame.add_entity(make_unique<Ball>((coord)25, Color4F::MAGENTA, LOC(580,300), VEL(100,100), true));
	ballgame.add_entity(make_unique<Ball>((coord)25, Color4F::YELLOW, LOC(260,500), VEL(-100,100), true));
	
	//random balls
	default_random_engine generator;
	uniform_real_distribution<float> zero2one(0.0, 1.0);
	uniform_real_distribution<float> half2half(-0.5, 0.5);
	srand((unsigned)time(0));
	for (int i = 0; i < 30; i++) {
		ballgame.add_entity(
			make_unique<Ball>(
				(coord)10.f,
				Color4F(0.f, 1.f, 0.f, 0.75f), 
				LOC(zero2one(generator) * 800, zero2one(generator) * 600),
				VEL(half2half(generator) * 500, half2half(generator) * 500),
				true
			)
		);
	}
}