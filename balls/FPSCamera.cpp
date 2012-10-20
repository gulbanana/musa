#include <engine/core.h>
#include <engine/components.h>
#include "FPSCamera.h"
using namespace std;

FPSCamera::FPSCamera(point initialLocation) : Camera3D(initialLocation)
{
	_components.emplace_back(make_unique<CInput>((coord)5));
	//look_at(point(initialLocation.x, initialLocation.y, initialLocation.z/(coord)2));
	//get_component<CPosition>()->orientation.x = 0;
}