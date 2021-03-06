#include <mesh/stdafx.h>
#include "SpriteMesh.h"
using namespace std;

void SpriteMesh::accept_enter(IRenderer* renderer) const
{ 
	renderer->visit_enter(this); 
}

void SpriteMesh::accept_leave(IRenderer* renderer) const
{ 
	renderer->visit_leave(this); 
}

box6 SpriteMesh::bounds() const
{
	//nominal depth
	return box6(width/(coord)2, height/(coord)2, (coord)-1, width/(coord)2, height/(coord)2, (coord)1);
}

size_t SpriteMesh::polygons() const
{
	return 0;
}

bool SpriteMesh::is_camera() const
{
	return false;
}