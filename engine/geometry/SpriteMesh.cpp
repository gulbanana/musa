#include <algorithm>
#include "SpriteMesh.h"
using namespace std;

void SpriteMesh::accept(IRenderer* renderer, Vec3<coord> position, Vec3<degrees> orientation) const
{ 
	renderer->visit(this, position, orientation); 
}

Box6<coord> SpriteMesh::bounds() const
{
	//nominal depth
	return Box6<coord>(width/(coord)2, height/(coord)2, (coord)-1, width/(coord)2, height/(coord)2, (coord)1);
}