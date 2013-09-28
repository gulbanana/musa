#include <engine/mesh/core.h>
#include "CTransform.h"

using namespace glm;

lnseg CTransform::direction_vector()
{
	//quat zq(0, z_axis.x, z_axis.y, z_axis.z);
	//quat fv = inverse(rotate) * zq;
	//return vec3(fv.x, fv.y, fv.z);

	//return normalize(rotate * z_axis);

	//return lnseg(2 * (rotate.x * rotate.z + rotate.w * rotate.y),
	//	         2 * (rotate.y * rotate.x - rotate.w * rotate.x),
	//			 1 - 2 * (rotate.x * rotate.x + rotate.y * rotate.y));

	quat p(0, constants::z_axis.x, constants::z_axis.y, constants::z_axis.z);
	quat qpq = rotate * p * conjugate(rotate);	//equivalent to inverse if normalised, and faster
	return vec3(qpq.x, qpq.y, qpq.z);

	//return vec3(transform->rotate * z_axis * transform->rotate);

	//return vec3(0,0,-1);

	//return rotate * z_axis;

}