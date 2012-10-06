#include <memory>
#include <random>
#include <ctime>
#include <engine/Engine.h>
#include <engine/Scene.h>
#include <engine/misc.h>
#include <engine/platform.h>
#include "Obstacle.h"
#include "Ball.h"
#include "BallBouncer.h"
using namespace std;

#define LOC(x, y) Vec2<coord>((coord)(x), (coord)(y))
#define VEL(x, y) Vec2<coord>((coord)(x), (coord)(y))
#define ROT(x, y, z) Vec3<degrees>((degrees)(x), (degrees)(y), (degrees)(z))
#define WIDTH 1200
#define HEIGHT 800

void setup_world(EntityGraph&);

extern "C"
int main(int argc, char *argv[])
{
	setenv("SDL_VIDEO_WINDOW_POS", "center", 1);
	setenv("SDL_VIDEO_CENTERED", "1", 1);

	EntityGraph level;
	Engine game(make_unique<BallBouncer>(WIDTH, HEIGHT), "balls!", WIDTH, HEIGHT);

	setup_world(level);
	game.load_scene(&level);
	game.play();

	return 0;
}

void setup_world(EntityGraph& ballgame)
{
	//immobiles
	ballgame.add_entity(make_unique<Obstacle>(Colour4F::WHITE, LOC(250, 400), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Obstacle>(Colour4F::WHITE, LOC(500, 400), ROT(45,90,0), false));
	ballgame.add_entity(make_unique<Obstacle>(Colour4F::WHITE, LOC(750, 400), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Obstacle>(Colour4F::WHITE, LOC(1000, 400), ROT(45,90,0), false));

	//fixed balls
	ballgame.add_entity(make_unique<Ball>((coord)35, Colour4F::CYAN, LOC(100,100), VEL(100,-100), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Ball>((coord)35, Colour4F::MAGENTA, LOC(580,300), VEL(100,100), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Ball>((coord)35, Colour4F::YELLOW, LOC(260,500), VEL(-100,100), ROT(0,0,0)));
	
	//random balls
	default_random_engine generator;
	uniform_real_distribution<float> zero2one(0.0, 1.0);
	uniform_real_distribution<float> half2half(-0.5, 0.5);
	uniform_real_distribution<float> threesixty(0.0, 360.0);
	srand((unsigned)time(0));
	for (int i = 0; i < 40; i++) {
		ballgame.add_entity(
			make_unique<Ball>(
				(coord)15,
				Colour4F(0.f, 1.f, 0.f, 0.75f), 
				LOC(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT),
				VEL(half2half(generator) * 500, half2half(generator) * 500),
				ROT(threesixty(generator), threesixty(generator), threesixty(generator))
			)
		);
	}
}