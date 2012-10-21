#pragma once
#include "IRenderable.h"
#include "IMaterial.h"

//Flat/quad mesh- 2d sprite chunked into ^2 fragments
struct SpriteMesh : public IRenderable
{
	coord width;
	coord height;
	std::shared_ptr<IMaterial> brush;
	
	SpriteMesh(coord width, coord height/*, texture*/);
	void accept_enter(IRenderer* renderer) const final;
	void accept_leave(IRenderer* renderer) const final;

	box6 bounds() const final;
	size_t polygons() const final; 
	bool is_camera() const final;
};

