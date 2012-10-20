#include <engine/core.h>
#include <engine/components.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Camera3D.h"

using namespace std;
using namespace maths;

Camera3D::Camera3D() : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)60, (coord)2048))
{
	//in the centre of the world, looking forward
	_components.emplace_back(make_unique<CPosition>(origin, forward_rotation));
	_components.emplace_back(make_unique<CTransform>(_camera_matrix.get()));
}

Camera3D::Camera3D(point initialLocation) : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)60, (coord)2048))
{
	//in front of the world, looking back at it
	_components.emplace_back(make_unique<CPosition>(initialLocation, rotation_from(initialLocation, origin)));
	_components.emplace_back(make_unique<CTransform>(_camera_matrix.get()));
}

Camera3D::Camera3D(point initialLocation, angles initialOrientation) : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)60, (coord)2048))
{
	//in front of the world, looking back at it
	_components.emplace_back(make_unique<CPosition>(initialLocation, initialOrientation));
	_components.emplace_back(make_unique<CTransform>(_camera_matrix.get()));
}

void Camera3D::move_to(IEntity* camera, point location)
{
	camera->get_component<CPosition>()->location = location;
}

void Camera3D::look_at(IEntity* camera, point location)
{
	auto position = camera->get_component<CPosition>();
	position->orientation = rotation_from(position->location, location);
}
