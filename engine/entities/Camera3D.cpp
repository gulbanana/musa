#include <engine/components.h>
#include <engine/misc.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Camera3D.h"

using namespace std;
using namespace maths;

Camera3D::Camera3D() : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)90, (coord)1000)))
{
	//in the centre of the world, looking forward
	add_component(make_unique<CPosition>(origin, forward_rotation));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
}

Camera3D::Camera3D(Vec3<coord> initialLocation) : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)90, (coord)1000))
{
	//in front of the world, looking back at it
	add_component(make_unique<CPosition>(initialLocation, rotation_from(initialLocation, origin)));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
}

Camera3D::Camera3D(Vec3<coord> initialLocation, Vec3<degrees> initialOrientation) : 
	_camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus, (degrees)90, (coord)1000)))
{
	//in front of the world, looking back at it
	add_component(make_unique<CPosition>(initialLocation, initialOrientation));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
}

void Camera3D::move_to(Vec3<coord> location)
{
	get_component<CPosition>()->location = location;
}

void Camera3D::look_at(Vec3<coord> location)
{
	auto position = get_component<CPosition>();
	position->orientation = rotation_from(position->location, location);
}
