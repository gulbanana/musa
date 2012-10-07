#include <memory>
#include <random>
#include <ctime>
#include <engine/Engine.h>
#include <engine/ResourceManager.h>
#include <engine/scene.h>
#include <engine/misc.h>
#include <engine/platform.h>
#include <engine/entities.h>
#include "Obstacle.h"
#include "Ball.h"
#include "BallBouncer.h"
using namespace std;

#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1000
#define LOC(x, y) Vec3<coord>((coord)(x), (coord)(y), (coord)500)
#define VEL(x, y) Vec3<coord>((coord)(x), (coord)(y), (coord)0)
#define ROT(x, y, z) Vec3<degrees>((degrees)(x), (degrees)(y), (degrees)(z))

void setup_world(EntityGraph&, ResourceManager&);

extern "C"
int main(int argc, char *argv[])
{
	setenv("SDL_VIDEO_WINDOW_POS", "center", 1);
	setenv("SDL_VIDEO_CENTERED", "1", 1);

	ResourceManager loader;
	EntityGraph level;
	Engine game(make_unique<BallBouncer>(WIDTH, HEIGHT, DEPTH), "balls!", 1200, 800);

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

	//root
	auto view = make_shared<Camera2D>(Box6<coord>((coord)0, (coord)0, (coord)0, (coord)WIDTH, (coord)HEIGHT, (coord)DEPTH));
	ballgame.add_entity(view);

	//immobiles
	auto whitePaint = ballpit.load_brush(Colour4F::WHITE);
	auto shape = Box6<coord>((coord)-40, (coord)-60, (coord)-40, (coord)40, (coord)60, (coord)40);
	auto box = ballpit.load_primitive((SolidColourBrush*)whitePaint, Primitive::Prism, &shape);

	view->children.push_back(make_shared<Obstacle>(box, LOC(200, 500), ROT(0,0,0)));
	view->children.push_back(make_shared<Obstacle>(box, LOC(400, 500), ROT(45,90,0), false));
	view->children.push_back(make_shared<Obstacle>(box, LOC(600, 500), ROT(0,0,0)));
	view->children.push_back(make_shared<Obstacle>(box, LOC(800, 500), ROT(45,90,0), false));

	//fixed balls
	auto big = (coord)35;
	auto bigBall = [&](Colour4F c){ return ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(c), Primitive::Sphere, &big); };
	view->children.push_back(make_shared<Ball>(bigBall(Colour4F::CYAN), LOC(800,800), VEL(100,-100), ROT(0,0,0)));
	view->children.push_back(make_shared<Ball>(bigBall(Colour4F::MAGENTA), LOC(200,500), VEL(100,100), ROT(0,0,0)));
	view->children.push_back(make_shared<Ball>(bigBall(Colour4F::YELLOW), LOC(800,200), VEL(-100,100), ROT(0,0,0)));
	
	//random balls
	auto small = (coord)15;
	auto smallGreenBall = ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(Colour4F(0.f, 1.f, 0.f, 0.75f)), Primitive::Sphere, &small);

	for (int i = 0; i < 40; i++) {
		view->children.push_back(
			make_shared<Ball>(
				smallGreenBall, 
				LOC(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT),
				VEL(half2half(generator) * 500, half2half(generator) * 500),
				ROT(0, 0, 0)
			)
		);
	}
}