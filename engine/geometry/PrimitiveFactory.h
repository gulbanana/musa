#pragma once
#include <memory>
#include "IRenderable.h"

class PrimitiveFactory
{
public:
	static std::unique_ptr<IRenderable> create_sphere(coord radius);
	static std::unique_ptr<IRenderable> create_cube(coord radius);
	static std::unique_ptr<IRenderable> create_prism(Box6<coord> bounds);
};

