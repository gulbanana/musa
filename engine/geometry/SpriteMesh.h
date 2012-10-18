#pragma once
#include "IModel.h"
#include "IMaterial.h"

//Flat/quad mesh- 2d sprite chunked into ^2 fragments
struct SpriteMesh : public IModel
{
	coord width;
	coord height;
	std::shared_ptr<IMaterial> brush;
	
	SpriteMesh(coord width, coord height/*, texture*/);
	void accept(IRenderer* renderer) const override;
	box6 bounds() const override;
};

