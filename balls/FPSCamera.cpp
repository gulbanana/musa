#include <engine/core.h>
#include <engine/components.h>
#include "FPSCamera.h"
using namespace std;

FPSCamera::FPSCamera(point initialLocation) : Camera3D(initialLocation, constants::backward_orientation)
{
	_components.emplace_back(make_unique<CInput>((coord)150));
	_components.emplace_back(make_unique<CVelocity>());
}