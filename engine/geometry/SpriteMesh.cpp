#include <engine/core.h>
#include <algorithm>
#include "SpriteMesh.h"
using namespace std;

void SpriteMesh::accept(IRenderer* renderer) const
{ 
	renderer->draw(this); 
}

box6 SpriteMesh::bounds() const
{
	//nominal depth
	return box6(width/(coord)2, height/(coord)2, (coord)-1, width/(coord)2, height/(coord)2, (coord)1);
}