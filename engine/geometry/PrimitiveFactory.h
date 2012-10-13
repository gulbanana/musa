#pragma once
#include <memory>
#include "IModel.h"
#include "IMaterial.h"

class PrimitiveFactory
{
public:
	static std::unique_ptr<IModel> create_sphere(IMaterial* brush, coord radius, int refinements = 2);
	static std::unique_ptr<IModel> create_cube(IMaterial* brush, coord radius);
	static std::unique_ptr<IModel> create_prism(IMaterial* brush, Box6<coord> bounds);
};

