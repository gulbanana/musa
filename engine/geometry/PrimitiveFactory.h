#pragma once
#include <memory>
#include "IRenderable.h"

class PrimitiveFactory
{
public:
	static std::unique_ptr<IRenderable> create_sphere(float radius);
	static std::unique_ptr<IRenderable> create_cube(float radius);
	static std::unique_ptr<IRenderable> create_prism(Box6F bounds);
};

