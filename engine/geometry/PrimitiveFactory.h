#pragma once
#include <memory>
#include "IRenderable.h"
#include "IMaterial.h"

class PrimitiveFactory
{
	std::shared_ptr<IMaterial> _brush;

public:
	PrimitiveFactory(std::shared_ptr<IMaterial> brush);
	std::unique_ptr<IRenderable> create_sphere(coord radius);
	std::unique_ptr<IRenderable> create_cube(coord radius);
	std::unique_ptr<IRenderable> create_prism(Box6<coord> bounds);
};

