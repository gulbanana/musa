#include <algorithm>
#include "VVMesh.h"
using namespace std;

void VVMesh::accept(IRenderer* renderer, Color4F brush, Vector3F position, Vector3F orientation) const
{ 
	renderer->visit(this, brush, position, orientation); 
}

Box6F VVMesh::bounds() const
{
	float minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = maxX = maxY = maxZ = 0.f;

	for (auto v : vertices)
	{
		minX = min(v.x, minX);
		minY = min(v.y, minY);
		minZ = min(v.z, minZ);
		maxX = max(v.x, maxX);
		maxY = max(v.y, maxY);
		maxZ = max(v.z, maxZ);
	}
	
	return Box6F(minX, minY, minZ, maxX, maxY, maxZ);
}