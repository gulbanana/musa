#include <algorithm>
#include "VVMesh.h"
using namespace std;

void VVMesh::accept(IRenderer* renderer, Color4F brush, Vec3<coord> position, Vec3<degrees> orientation) const
{ 
	renderer->visit(this, brush, position, orientation); 
}

Box6<coord> VVMesh::bounds() const
{
	return bounds_cache;
}

VVMesh::VVMesh(vector<VVMesh::Vertex>&& v) : vertices(v), bounds_cache((coord)0, (coord)0, (coord)0, (coord)0, (coord)0, (coord)0)
{
	for (auto v : vertices)
	{
		bounds_cache.x1 = min(v.x, bounds_cache.x1);
		bounds_cache.y1 = min(v.y, bounds_cache.y1);
		bounds_cache.z1 = min(v.z, bounds_cache.z1);
		bounds_cache.x2 = max(v.x, bounds_cache.x2);
		bounds_cache.y2 = max(v.y, bounds_cache.y2);
		bounds_cache.z2 = max(v.z, bounds_cache.z2);
	}
}