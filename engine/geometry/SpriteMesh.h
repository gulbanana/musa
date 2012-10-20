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
	void invite(IRenderer* renderer) const final;
	void accept(IRenderer* renderer) const final;
	box6 bounds() const;
};

