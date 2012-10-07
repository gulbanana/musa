#pragma once
#include <engine/scene.h>
#include <engine/geometry.h>

//conceptually, a camera entity is positioned and oriented in world-space like any other
class Camera2D : public BranchNode
{
	std::unique_ptr<OrthographicCamera> _camera_matrix;

public:
	Camera2D(Box6<coord> bounds, bool anamorphic = false);
};

