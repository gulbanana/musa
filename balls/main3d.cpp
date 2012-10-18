#include <engine/core.h>
#include <engine/Engine.h>
#include <engine/ResourceManager.h>
#include <engine/scene.h>
#include <engine/misc.h>
#include <engine/entities.h>
#include <random>
#include <ctime>
#include "Obstacle.h"
#include "Ball.h"
#include "Bouncer.h"
#include "FPSCamera.h"
#include "FPSController.h"
using namespace std;

#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1000
#define LOC(x, y, z) point((coord)(x), (coord)(y), (coord)(z))
#define VEL(x, y, z) point((coord)(x), (coord)(y), (coord)(z))
#define ROT(x, y, z) angles((degrees)(x), (degrees)(y), (degrees)(z))

void setup_world(EntityGraph&, ResourceManager&);

extern "C"
int main(int argc, char *argv[])
{
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");

	vector<unique_ptr<ISystem>> customs;
	customs.push_back(make_unique<Bouncer>(WIDTH, HEIGHT, DEPTH));
	customs.push_back(make_unique<FPSController>());

	ResourceManager loader;
	EntityGraph level;
	Settings settings("balls 3d!", 1200, 675, GraphicsMode::THREE_D);
	Engine game(settings, move(customs));

	setup_world(level, loader);
	game.load_scene(level);
	game.play();

	return 0;
}

void setup_world(EntityGraph& ballgame, ResourceManager& ballpit)
{
	default_random_engine generator;
	uniform_real_distribution<glm::float_t> zero2one(0.0, 1.0);
	uniform_real_distribution<glm::float_t> half2half(-0.5, 0.5);
	uniform_real_distribution<glm::float_t> threesixty(0.0, 360.0);

	//root
	auto view = make_shared<FPSCamera>(LOC(WIDTH/2, HEIGHT/2, DEPTH));
	ballgame.add_entity(view);

	//immobiles
	auto whitePaint = ballpit.load_brush(Colour::WHITE);
	auto redPaint = ballpit.load_brush(Colour::RED);
	auto bluePaint = ballpit.load_brush(Colour::BLUE);

	auto smallBox = box6((coord)-50, (coord)-150, (coord)-30, (coord)50, (coord)150, (coord)30);
	auto bigBox = box6((coord)-500, (coord)-500, (coord)-500, (coord)500, (coord)500, (coord)500);

	auto bluePlatform = ballpit.load_primitive((SolidColourBrush*)bluePaint, Primitive::Prism, &smallBox);
	auto redPlatform = ballpit.load_primitive((SolidColourBrush*)redPaint, Primitive::Prism, &smallBox);
	auto whiteBounds = ballpit.load_primitive((SolidColourBrush*)whitePaint, Primitive::Prism, &bigBox);

	view->children.push_back(make_shared<Obstacle>(redPlatform, LOC(200, 500, WIDTH/2), ROT(0,0,0)));
	view->children.push_back(make_shared<Obstacle>(bluePlatform, LOC(400, 500, WIDTH/2), ROT(0,45,0), false));
	view->children.push_back(make_shared<Obstacle>(redPlatform, LOC(600, 500, WIDTH/2), ROT(0,0,0)));
	view->children.push_back(make_shared<Obstacle>(bluePlatform, LOC(800, 500, WIDTH/2), ROT(45,0,0), false));

	//fixed balls
	auto big = (coord)35;
	auto bigBall = [&](colour c){ return ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(c), Primitive::Sphere, &big); };
	view->children.push_back(make_shared<Ball>(bigBall(Colour::CYAN), LOC(800,800,0), VEL(100,-100,0), ROT(0,0,0)));
	view->children.push_back(make_shared<Ball>(bigBall(Colour::MAGENTA), LOC(200,500,0), VEL(100,100,0), ROT(0,0,0)));
	view->children.push_back(make_shared<Ball>(bigBall(Colour::YELLOW), LOC(800,200,0), VEL(-100,100,0), ROT(0,0,0)));
	
	//random balls
	auto small = (coord)15;
	auto smallGreenBall = ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(colour(0.f, 1.f, 0.f, 0.75f)), Primitive::Sphere, &small);

	for (int i = 0; i < 50; i++) {
		view->children.push_back(
			make_shared<Ball>(
				smallGreenBall, 
				LOC(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT, zero2one(generator) * DEPTH),
				VEL(half2half(generator) * 500, half2half(generator) * 500, half2half(generator) * 500),
				ROT(0, 0, 0)
			)
		);
	}

	//skybox
	view->children.push_back(make_shared<Obstacle>(whiteBounds, LOC(500, 500, 500), ROT(0,0,0), false));
}