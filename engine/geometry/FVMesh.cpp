#include <algorithm>
#include "FVMesh.h"
using namespace std;

void FVMesh::accept(IRenderer* renderer, Color4F brush, Vec3<coord> position, Vec3<degrees> orientation) const
{ 
	renderer->visit(this, brush, position, orientation); 
}

Box6<coord> FVMesh::bounds() const
{
	coord minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = maxX = maxY = maxZ = 0.0;

	for (auto v : vertices)
	{
		minX = min(v.x, minX);
		minY = min(v.y, minY);
		minZ = min(v.z, minZ);
		maxX = max(v.x, maxX);
		maxY = max(v.y, maxY);
		maxZ = max(v.z, maxZ);
	}
	
	return Box6<coord>(minX, minY, minZ, maxX, maxY, maxZ);
}