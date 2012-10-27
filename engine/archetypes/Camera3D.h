#pragma once
#include <engine/geometry.h>
#include "PresetArchetype.h"

//conceptually, a camera entity is positioned and oriented in world-space like any other
class Camera3D : public PresetArchetype
{
	std::unique_ptr<PerspectiveCamera> _camera_matrix; //XXX the archetype should not own this renderable

public:
	Camera3D();
	Camera3D(point initialLocation);
	Camera3D(point initialLocation, rotation initialOrientation);

	//XXX these should be messages or something
	static void move_to(IEntity* camera, point location);
	static void look_at(IEntity* camera, point location);
};

