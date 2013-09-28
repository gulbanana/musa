#pragma once
#include <core/framework.h>
#include "../geometry.h"

class Camera2D final: public ArchetypeBase
{
	std::unique_ptr<OrthographicCamera> _camera_matrix;	//XXX the archetype should not own this renderable

public:
	Camera2D(coord width, coord height, coord depth, bool anamorphic = false);
};

