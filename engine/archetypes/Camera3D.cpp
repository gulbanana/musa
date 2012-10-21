#include <engine/core.h>
#include <engine/components.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Camera3D.h"

using namespace std;
using namespace maths;

//in the centre of the world, looking forward
Camera3D::Camera3D() : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)60, (coord)2048))
{
	_components.emplace_back(make_unique<CRenderable>(_camera_matrix.get()));
	_components.emplace_back(make_unique<CTransform>(origin, forward_rotation));
}

//in front of the world, looking back at it
Camera3D::Camera3D(point initialLocation) : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)60, (coord)2048))
{
	_components.emplace_back(make_unique<CRenderable>(_camera_matrix.get()));
	_components.emplace_back(make_unique<CTransform>(initialLocation, rotation_between(initialLocation, origin)));
}

Camera3D::Camera3D(point initialLocation, angle initialOrientation) : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)60, (coord)2048))
{
	_components.emplace_back(make_unique<CRenderable>(_camera_matrix.get()));
	_components.emplace_back(make_unique<CTransform>(initialLocation, initialOrientation));
}

void Camera3D::move_to(IEntity* camera, point location)
{
	camera->get_component<CTransform>()->translate = location;
}

void Camera3D::look_at(IEntity* camera, point location)
{
	auto position = camera->get_component<CTransform>();
	position->rotate = rotation_between(position->translate, location);
}
