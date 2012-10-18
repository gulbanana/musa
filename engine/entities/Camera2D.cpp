#include <engine/core.h>
#include <engine/components.h>
#include <engine/misc.h>
#include "Camera2D.h"

using namespace std;

Camera2D::Camera2D(coord width, coord height, coord depth, bool anamorphic) : 
	_camera_matrix(
		new OrthographicCamera(
			Box6<coord>(maths::origin, width, height, depth), 
			anamorphic ? ScaleMethod::Anamorphic : ScaleMethod::HorPlus
		)
	)
{
	//in front of the world, looking back at it
	add_component(make_unique<CPosition>(
		Vec3<coord>(width/(coord)2, height/(coord)2, depth), 
		maths::backward_rotation
	));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
}

void Camera2D::resize(coord width, coord height, coord depth)
{
	_camera_matrix->range = Box6<coord>(maths::origin, width, height, depth);
	get_component<CPosition>()->location = Vec3<coord>(width/(coord)2, height/(coord)2, depth);
}