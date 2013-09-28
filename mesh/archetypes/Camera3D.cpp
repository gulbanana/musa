#include <mesh/stdafx.h>
#include <mesh/components.h>
#include <core/misc.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Camera3D.h"

using namespace std;

//in the centre of the world, looking forward
Camera3D::Camera3D() : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (angle)60, (coord)2048))
{
	_components.emplace_back(make_unique<CRenderable>(_camera_matrix.get()));
	_components.emplace_back(make_unique<CTransform>(constants::origin, constants::forward_orientation));
}

//in front of the world, looking back at it
Camera3D::Camera3D(point initialLocation) : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (angle)60, (coord)2048))
{
	_components.emplace_back(make_unique<CRenderable>(_camera_matrix.get()));
	_components.emplace_back(make_unique<CTransform>(initialLocation, constants::rotation_between(initialLocation, constants::origin)));
}

Camera3D::Camera3D(point initialLocation, rotation initialOrientation) : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (angle)60, (coord)2048))
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
	position->rotate = constants::rotation_between(position->translate, location);
}
