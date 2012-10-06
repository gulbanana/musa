#include <memory>
#include <random>
#include <ctime>
#include <engine/Engine.h>
#include <engine/ResourceManager.h>
#include <engine/scene.h>
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

void setup_world(EntityGraph&, ResourceManager&);

extern "C"
int main(int argc, char *argv[])
{
	setenv("SDL_VIDEO_WINDOW_POS", "center", 1);
	setenv("SDL_VIDEO_CENTERED", "1", 1);

	ResourceManager loader;
	EntityGraph level;
	Engine game(make_unique<BallBouncer>(WIDTH, HEIGHT), "balls!", WIDTH, HEIGHT);

	setup_world(level, loader);
	game.load_scene(&level);
	game.play();

	return 0;
}

void setup_world(EntityGraph& ballgame, ResourceManager& ballpit)
{
	default_random_engine generator;
	uniform_real_distribution<float> zero2one(0.0, 1.0);
	uniform_real_distribution<float> half2half(-0.5, 0.5);
	uniform_real_distribution<float> threesixty(0.0, 360.0);

	//immobiles
	auto whitePaint = ballpit.load_brush(Colour4F::WHITE);
	auto shape = Box6<coord>((coord)-40, (coord)-60, (coord)-40, (coord)40, (coord)60, (coord)40);
	auto box = ballpit.load_primitive((SolidColourBrush*)whitePaint, Primitive::Prism, &shape);

	ballgame.add_entity(make_unique<Obstacle>(box, LOC(250, 400), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Obstacle>(box, LOC(500, 400), ROT(45,90,0), false));
	ballgame.add_entity(make_unique<Obstacle>(box, LOC(750, 400), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Obstacle>(box, LOC(1000, 400), ROT(45,90,0), false));

	//fixed balls
	auto big = (coord)35;
	auto bigBall = [&](Colour4F c){ return ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(c), Primitive::Sphere, &big); };
	ballgame.add_entity(make_unique<Ball>(bigBall(Colour4F::CYAN), LOC(100,100), VEL(100,-100), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Ball>(bigBall(Colour4F::MAGENTA), LOC(580,300), VEL(100,100), ROT(0,0,0)));
	ballgame.add_entity(make_unique<Ball>(bigBall(Colour4F::YELLOW), LOC(260,500), VEL(-100,100), ROT(0,0,0)));
	
	//random balls
	auto small = (coord)15;
	auto smallGreenBall = ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(Colour4F(0.f, 1.f, 0.f, 0.75f)), Primitive::Sphere, &small);

	for (int i = 0; i < 40; i++) {
		ballgame.add_entity(
			make_unique<Ball>(
				smallGreenBall, 
				LOC(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT),
				VEL(half2half(generator) * 500, half2half(generator) * 500),
				ROT(0, 0, 0)
			)
		);
	}
}