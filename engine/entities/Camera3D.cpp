#include "Camera3D.h"
#include <engine/components.h>
#include <engine/misc.h>
using namespace std;

Camera3D::Camera3D() : _camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus))
{
	//in front of the world, looking back at it
	add_component(make_unique<CPosition>(
		Vec3<coord>((coord)0, (coord)0, 0), 
		Vec3<degrees>((degrees)0, (degrees)0, (degrees)0)
	));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
}

void Camera3D::move_to(Vec3<coord> location)
{
	get_component<CPosition>()->location = location;
}

void Camera3D::look_at(Vec3<coord> location)
{
}