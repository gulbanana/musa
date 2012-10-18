#include <engine/core.h>
#include <engine/Engine.h>
#include <engine/ResourceManager.h>
#include <engine/scene.h>
#include <engine/misc.h>
#include <engine/entities.h>
#include <balls/Obstacle.h>
#include <balls/Ball.h>
#include <balls/ResizingBouncer.h>
#include <random>
#include <ctime>
using namespace std;

#define WIDTH 1200
#define HEIGHT 800
#define DEPTH HEIGHT
#define LOC(x, y) Vec3<coord>((coord)(x), (coord)(y), (coord)(DEPTH/2))
#define VEL(x, y) Vec3<coord>((coord)(x), (coord)(y), (coord)(0))
#define ROT(z) Vec3<degrees>((degrees)(0), (degrees)(0), (degrees)(z))

void setup_world(EntityGraph&, ResourceManager&);

extern "C"
int main(int argc, char *argv[])
{
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");

	//create engine objects
	ResourceManager ballpit;
	EntityGraph ballgame;
	Settings settings("balls!", WIDTH, HEIGHT, GraphicsMode::TWO_D);

	//useful random functions
	default_random_engine generator;
	uniform_real_distribution<float> zero2one(0.0, 1.0);
	uniform_real_distribution<float> half2half(-0.5, 0.5);
	uniform_real_distribution<float> threesixty(0.0, 360.0);

	//root
	auto view = make_shared<Camera2D>((coord)WIDTH, (coord)HEIGHT, (coord)HEIGHT);
	ballgame.add_entity(view);

	//immobiles
	auto redPaint = ballpit.load_brush(Colour::RED);
	auto whitePaint = ballpit.load_brush(Colour::WHITE);

	auto smallBox = Box6<coord>((coord)-50, (coord)-80, (coord)-30, (coord)50, (coord)80, (coord)30);

	auto bluePlatform = ballpit.load_primitive((SolidColourBrush*)whitePaint, Primitive::Prism, &smallBox);
	auto redPlatform = ballpit.load_primitive((SolidColourBrush*)redPaint, Primitive::Prism, &smallBox);

	view->children.push_back(make_shared<Obstacle>(redPlatform, LOC(250, 400), ROT(0)));
	view->children.push_back(make_shared<Obstacle>(bluePlatform, LOC(500, 400), ROT(45), false));
	view->children.push_back(make_shared<Obstacle>(redPlatform, LOC(750, 400), ROT(0)));
	view->children.push_back(make_shared<Obstacle>(bluePlatform, LOC(1000, 400), ROT(45), false));

	//fixed balls
	auto big = (coord)35;
	auto bigBall = [&](colour c){ return ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(c), Primitive::Sphere, &big); };
	view->children.push_back(make_shared<Ball>(bigBall(Colour::CYAN), LOC(800,800), VEL(100,-100), ROT(0)));
	view->children.push_back(make_shared<Ball>(bigBall(Colour::MAGENTA), LOC(200,500), VEL(100,100), ROT(0)));
	view->children.push_back(make_shared<Ball>(bigBall(Colour::YELLOW), LOC(800,200), VEL(-100,100), ROT(0)));
	
	//random balls
	auto small = (coord)15;
	auto smallGreenBall = ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(colour(0.f, 1.f, 0.f, 0.75f)), Primitive::Sphere, &small);

	for (int i = 0; i < 35; i++) {
		view->children.push_back(
			make_shared<Ball>(
				smallGreenBall, 
				LOC(zero2one(generator) * WIDTH, zero2one(generator) * HEIGHT),
				VEL(half2half(generator) * 500, half2half(generator) * 500),
				ROT(0)
			)
		);
	}

	/* run the game */
	vector<unique_ptr<ISystem>> customs;
	customs.push_back(make_unique<ResizingBouncer>(view, WIDTH, HEIGHT, DEPTH));

	Engine game(settings, move(customs));
	game.load_scene(ballgame);
	game.play();

	return 0;
}