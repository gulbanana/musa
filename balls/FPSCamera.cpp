#include <engine/core.h>
#include <engine/misc.h>
#include <engine/components.h>
#include "FPSCamera.h"
using namespace std;

FPSCamera::FPSCamera(Vec3<coord> initialLocation) : Camera3D(initialLocation)
{
	add_component(make_unique<CPlayer>((coord)5));
	look_at(Vec3<coord>(initialLocation.x, initialLocation.y, initialLocation.z/(coord)2));
	get_component<CPosition>()->orientation.x = 0;
}