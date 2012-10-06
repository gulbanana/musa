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
#define WIDTH 1600
#define HEIGHT 800

void setup_world(World&);

extern "C"
int main(int argc, char *argv[])
{
	auto game = World("balls!", WIDTH, HEIGHT);
	setup_world(game);
	game.play();

	return 0;
}

void setup_world(World& ballgame)
{
	//special logic system
	ballgame.add_system(make_unique<BallBouncer>(WIDTH, HEIGHT));

	//immobiles
	ballgame.add_entity(make_unique<Obstacle>(Color4F::WHITE, LOC(300, 400), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Obstacle>(Color4F::WHITE, LOC(600, 400), ROT(45,90,0), false));
	ballgame.add_entity(make_unique<Obstacle>(Color4F::WHITE, LOC(900, 400), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Obstacle>(Color4F::WHITE, LOC(1200, 400), ROT(45,90,0), false));

	//fixed balls
	ballgame.add_entity(make_unique<Ball>((coord)25, Color4F::CYAN, LOC(100,100), VEL(100,-100), true));
	ballgame.add_entity(make_unique<Ball>((coord)25, Color4F::MAGENTA, LOC(580,300), VEL(100,100), true));
	ballgame.add_entity(make_unique<Ball>((coord)25, Color4F::YELLOW, LOC(260,500), VEL(-100,100), true));
	
	//random balls
	default_random_engine generator;
	uniform_real_distribution<float> zero2one(0.0, 1.0);
	uniform_real_distribution<float> half2half(-0.5, 0.5);
	srand((unsigned)time(0));
	for (int i = 0; i < 40; i++) {
		ballgame.add_entity(
			make_unique<Ball>(
				(coord)10.f,
				Color4F(0.f, 1.f, 0.f, 0.75f), 
				LOC(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT),
				VEL(half2half(generator) * 500, half2half(generator) * 500),
				true
			)
		);
	}
}