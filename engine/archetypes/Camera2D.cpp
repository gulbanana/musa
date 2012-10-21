#include <engine/core.h>
#include <engine/components.h>
#include "Camera2D.h"
using namespace std;

//create a camera in front of the world, looking back at it
Camera2D::Camera2D(coord width, coord height, coord depth, bool anamorphic) : 
	_camera_matrix(
		new OrthographicCamera(
			box6(maths::origin, width, height, depth), 
			anamorphic ? ScaleMethod::Anamorphic : ScaleMethod::HorPlus
		)
	)
{
	_components.emplace_back(make_unique<CTransform>(
		point(width/2, height/2, depth), 
		maths::backward_rotation
	));

	_components.emplace_back(make_unique<CRenderable>(_camera_matrix.get()));
}