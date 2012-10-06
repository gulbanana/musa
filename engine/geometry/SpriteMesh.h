#pragma once
#include <vector>
#include <engine/core.h>
#include "IRenderable.h"
#include "IMaterial.h"

//Flat/quad mesh- 2d sprite chunked into ^2 fragments
struct SpriteMesh : public IRenderable
{
	coord width;
	coord height;
	std::shared_ptr<IMaterial> brush;
	
	SpriteMesh(coord width, coord height/*, texture*/);
	void accept(IRenderer* renderer, Vec3<coord> position, Vec3<degrees> orientation) const override;
	Box6<coord> bounds() const override;
};

