#include "Camera2D.h"
#include <engine/components.h>
#include <engine/misc.h>
using namespace std;

Camera2D::Camera2D(Box6<coord> bounds, bool anamorphic) : _camera_matrix(new OrthographicCamera(bounds, anamorphic ? ScaleMethod::Anamorphic : ScaleMethod::HorPlus))
{
	//in front of the world, looking back at it
	add_component(make_unique<CPosition>(
		Vec3<coord>(bounds.width()/(coord)2, bounds.height()/(coord)2, bounds.depth()), 
		Vec3<degrees>((degrees)0, (degrees)0, (degrees)0)
	));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
}