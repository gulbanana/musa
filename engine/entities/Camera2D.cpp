#include "Camera2D.h"
#include <engine/components.h>
#include <engine/misc.h>
using namespace std;

Camera2D::Camera2D(coord depth) : _camera_matrix(new OrthographicCamera(depth))
{
	//1 unit in front of the world, looking back at it
	add_component(make_unique<CPosition>(Vec3<coord>((coord)0, (coord)0, (coord)1), Vec3<degrees>((degrees)0, (degrees)0, (degrees)180)));
	add_component(make_unique<CTransform>(_camera_matrix.get()));
}