#include "Camera3D.h"
#include <engine/components.h>
#include <engine/misc.h>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

Camera3D::Camera3D() : _camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus))
{
	//in front of the world, looking back at it
	add_component(make_unique<CPosition>(Vec3<coord>::origin(), Vec3<degrees>::origin()));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
}

Camera3D::Camera3D(Vec3<coord> initialLocation) : _camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus))
{
	//in front of the world, looking back at it
	add_component(make_unique<CPosition>(initialLocation, angle_from(initialLocation, Vec3<coord>::origin())));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
	add_component(make_unique<CVelocity>((coord)-5, (coord)0, (coord)0));
	add_component(make_unique<CAcceleration>(Vec3<coord>((coord)0, (coord)0, (coord)-2), Vec3<degrees>((degrees)0, (degrees)1, (degrees)0)));

}

Camera3D::Camera3D(Vec3<coord> initialLocation, Vec3<degrees> initialOrientation) : _camera_matrix(new PerspectiveCamera(ScaleMethod::HorPlus))
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
	position->orientation = angle_from(position->location, location);
}

Vec3<degrees> Camera3D::angle_from(Vec3<coord> from, Vec3<coord> to)
{
	auto angle = [](coord x1, coord y1, coord x2, coord y2)
	{
		auto dx = x2 - x1;
		auto dy = y2 - y1;
		auto rad = atan2(dy, dx);
		return (degrees)(rad * 180/M_PI);
	};

	degrees zangle = angle(from.x, from.y, to.x, to.y);
	degrees xangle = angle(from.y, from.z, to.y, to.z);
	degrees yangle = angle(from.z, from.x, to.z, to.x);

	return Vec3<degrees>(xangle, yangle, zangle);
}