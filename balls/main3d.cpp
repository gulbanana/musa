#include <memory>
#include <random>
#include <ctime>
#include <engine/Engine.h>
#include <engine/ResourceManager.h>
#include <engine/scene.h>
#include <engine/misc.h>
#include <engine/platform.h>
#include <engine/entities.h>
#include <balls/Obstacle.h>
#include <balls/Ball.h>
#include <balls/Bouncer.h>
using namespace std;

#define WIDTH 1000
#define HEIGHT 1000
#define DEPTH 1000
#define LOC(x, y, z) Vec3<coord>((coord)(x), (coord)(y), (coord)(z))
#define VEL(x, y, z) Vec3<coord>((coord)(x), (coord)(y), (coord)(z))
#define ROT(x, y, z) Vec3<degrees>((degrees)(x), (degrees)(y), (degrees)(z))

void setup_world(EntityGraph&, ResourceManager&);

extern "C"
int main(int argc, char *argv[])
{
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");

	ResourceManager loader;
	EntityGraph level;
	Settings settings("balls!", 1200, 800, GraphicsMode::THREE_D);
	Engine game(settings, make_unique<Bouncer>(WIDTH, HEIGHT, DEPTH));

	setup_world(level, loader);
	game.load_scene(level);
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
	//auto view = make_shared<Camera2D>(Box6<coord>((coord)0, (coord)0, (coord)0, (coord)WIDTH, (coord)HEIGHT, (coord)DEPTH));
	auto view = make_shared<Camera3D>(LOC(WIDTH/2, HEIGHT/2, DEPTH));
	view->look_at(LOC(WIDTH/2, HEIGHT/2, DEPTH/2));
	ballgame.add_entity(view);

	//immobiles
	auto whitePaint = ballpit.load_brush(Colour4F::WHITE);
	auto redPaint = ballpit.load_brush(Colour4F::RED);
	auto bluePaint = ballpit.load_brush(Colour4F::BLUE);

	auto smallBox = Box6<coord>((coord)-50, (coord)-80, (coord)-30, (coord)50, (coord)80, (coord)30);
	auto bigBox = Box6<coord>((coord)-500, (coord)-500, (coord)-500, (coord)500, (coord)500, (coord)500);

	auto bluePlatform = ballpit.load_primitive((SolidColourBrush*)bluePaint, Primitive::Prism, &smallBox);
	auto redPlatform = ballpit.load_primitive((SolidColourBrush*)redPaint, Primitive::Prism, &smallBox);
	auto whiteBounds = ballpit.load_primitive((SolidColourBrush*)whitePaint, Primitive::Prism, &bigBox);

	view->children.push_back(make_shared<Obstacle>(redPlatform, LOC(200, 500, WIDTH/2), ROT(0,0,0)));
	view->children.push_back(make_shared<Obstacle>(bluePlatform, LOC(400, 500, WIDTH/2), ROT(45,90,0), false));
	view->children.push_back(make_shared<Obstacle>(redPlatform, LOC(600, 500, WIDTH/2), ROT(0,0,0)));
	view->children.push_back(make_shared<Obstacle>(bluePlatform, LOC(800, 500, WIDTH/2), ROT(45,90,0), false));
	view->children.push_back(make_shared<Obstacle>(whiteBounds, LOC(500, 500, 500), ROT(0,0,0), false));

	//fixed balls
	auto big = (coord)35;
	auto bigBall = [&](Colour4F c){ return ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(c), Primitive::Sphere, &big); };
	view->children.push_back(make_shared<Ball>(bigBall(Colour4F::CYAN), LOC(800,800,0), VEL(100,-100,0), ROT(0,0,0)));
	view->children.push_back(make_shared<Ball>(bigBall(Colour4F::MAGENTA), LOC(200,500,0), VEL(100,100,0), ROT(0,0,0)));
	view->children.push_back(make_shared<Ball>(bigBall(Colour4F::YELLOW), LOC(800,200,0), VEL(-100,100,0), ROT(0,0,0)));
	
	//random balls
	auto small = (coord)15;
	auto smallGreenBall = ballpit.load_primitive((SolidColourBrush*)ballpit.load_brush(Colour4F(0.f, 1.f, 0.f, 0.75f)), Primitive::Sphere, &small);

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
}