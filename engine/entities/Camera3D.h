#pragma once
#include <engine/scene.h>
#include <engine/geometry.h>

//conceptually, a camera entity is positioned and oriented in world-space like any other
class Camera3D : public BranchNode
{
	std::unique_ptr<PerspectiveCamera> _camera_matrix;

public:
	Camera3D();
	void move_to(Vec3<coord> location);
	void look_at(Vec3<coord> location);
};

