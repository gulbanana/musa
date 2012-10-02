#pragma once
#include <memory>
#include <engine/misc.h>
#include "PrimitiveFactory.h"
#include "VVMesh.h"
using namespace std;

unique_ptr<IRenderable> PrimitiveFactory::create_cube(float radius)
{
	auto geometry = make_unique<VVMesh>();

	geometry->vertices.emplace_back(-radius, -radius, -radius);
	geometry->vertices[0].adjacent.push_back(1);
	geometry->vertices[0].adjacent.push_back(3);
	geometry->vertices[0].adjacent.push_back(4);

	geometry->vertices.emplace_back(radius, -radius, -radius);
	geometry->vertices[1].adjacent.push_back(0);
	geometry->vertices[1].adjacent.push_back(2);
	geometry->vertices[1].adjacent.push_back(5);

	geometry->vertices.emplace_back(radius, radius, -radius);
	geometry->vertices[2].adjacent.push_back(1);
	geometry->vertices[2].adjacent.push_back(3);
	geometry->vertices[2].adjacent.push_back(6);

	geometry->vertices.emplace_back(-radius, radius, -radius);
	geometry->vertices[3].adjacent.push_back(0);
	geometry->vertices[3].adjacent.push_back(2);
	geometry->vertices[3].adjacent.push_back(7);

	geometry->vertices.emplace_back(-radius, -radius, radius);
	geometry->vertices[4].adjacent.push_back(5);
	geometry->vertices[4].adjacent.push_back(7);
	geometry->vertices[4].adjacent.push_back(0);

	geometry->vertices.emplace_back(radius, -radius, radius);
	geometry->vertices[5].adjacent.push_back(4);
	geometry->vertices[5].adjacent.push_back(6);
	geometry->vertices[5].adjacent.push_back(1);

	geometry->vertices.emplace_back(radius, radius, radius);
	geometry->vertices[4].adjacent.push_back(5);
	geometry->vertices[4].adjacent.push_back(7);
	geometry->vertices[4].adjacent.push_back(2);

	geometry->vertices.emplace_back(-radius, radius, radius);
	geometry->vertices[5].adjacent.push_back(4);
	geometry->vertices[5].adjacent.push_back(6);
	geometry->vertices[5].adjacent.push_back(3);

	return static_pointer_cast<IRenderable>(std::move(geometry));
}

unique_ptr<IRenderable> PrimitiveFactory::create_prism(Box6F bounds)
{
		auto geometry = make_unique<VVMesh>();
		float radius = 50.f;

	geometry->vertices.emplace_back(-radius, -radius, -radius);
	geometry->vertices[0].adjacent.push_back(1);
	geometry->vertices[0].adjacent.push_back(3);
	geometry->vertices[0].adjacent.push_back(4);

	geometry->vertices.emplace_back(radius, -radius, -radius);
	geometry->vertices[1].adjacent.push_back(0);
	geometry->vertices[1].adjacent.push_back(2);
	geometry->vertices[1].adjacent.push_back(5);

	geometry->vertices.emplace_back(radius, radius, -radius);
	geometry->vertices[2].adjacent.push_back(1);
	geometry->vertices[2].adjacent.push_back(3);
	geometry->vertices[2].adjacent.push_back(6);

	geometry->vertices.emplace_back(-radius, radius, -radius);
	geometry->vertices[3].adjacent.push_back(0);
	geometry->vertices[3].adjacent.push_back(2);
	geometry->vertices[3].adjacent.push_back(7);

	geometry->vertices.emplace_back(-radius, -radius, radius);
	geometry->vertices[4].adjacent.push_back(5);
	geometry->vertices[4].adjacent.push_back(7);
	geometry->vertices[4].adjacent.push_back(0);

	geometry->vertices.emplace_back(radius, -radius, radius);
	geometry->vertices[5].adjacent.push_back(4);
	geometry->vertices[5].adjacent.push_back(6);
	geometry->vertices[5].adjacent.push_back(1);

	geometry->vertices.emplace_back(radius, radius, radius);
	geometry->vertices[4].adjacent.push_back(5);
	geometry->vertices[4].adjacent.push_back(7);
	geometry->vertices[4].adjacent.push_back(2);

	geometry->vertices.emplace_back(-radius, radius, radius);
	geometry->vertices[5].adjacent.push_back(4);
	geometry->vertices[5].adjacent.push_back(6);
	geometry->vertices[5].adjacent.push_back(3);

	return static_pointer_cast<IRenderable>(std::move(geometry));
}

unique_ptr<IRenderable> PrimitiveFactory::create_sphere(float radius)
{
		auto geometry = make_unique<VVMesh>();

	geometry->vertices.emplace_back(-radius, -radius, -radius);
	geometry->vertices[0].adjacent.push_back(1);
	geometry->vertices[0].adjacent.push_back(3);
	geometry->vertices[0].adjacent.push_back(4);

	geometry->vertices.emplace_back(radius, -radius, -radius);
	geometry->vertices[1].adjacent.push_back(0);
	geometry->vertices[1].adjacent.push_back(2);
	geometry->vertices[1].adjacent.push_back(5);

	geometry->vertices.emplace_back(radius, radius, -radius);
	geometry->vertices[2].adjacent.push_back(1);
	geometry->vertices[2].adjacent.push_back(3);
	geometry->vertices[2].adjacent.push_back(6);

	geometry->vertices.emplace_back(-radius, radius, -radius);
	geometry->vertices[3].adjacent.push_back(0);
	geometry->vertices[3].adjacent.push_back(2);
	geometry->vertices[3].adjacent.push_back(7);

	geometry->vertices.emplace_back(-radius, -radius, radius);
	geometry->vertices[4].adjacent.push_back(5);
	geometry->vertices[4].adjacent.push_back(7);
	geometry->vertices[4].adjacent.push_back(0);

	geometry->vertices.emplace_back(radius, -radius, radius);
	geometry->vertices[5].adjacent.push_back(4);
	geometry->vertices[5].adjacent.push_back(6);
	geometry->vertices[5].adjacent.push_back(1);

	geometry->vertices.emplace_back(radius, radius, radius);
	geometry->vertices[4].adjacent.push_back(5);
	geometry->vertices[4].adjacent.push_back(7);
	geometry->vertices[4].adjacent.push_back(2);

	geometry->vertices.emplace_back(-radius, radius, radius);
	geometry->vertices[5].adjacent.push_back(4);
	geometry->vertices[5].adjacent.push_back(6);
	geometry->vertices[5].adjacent.push_back(3);

	return static_pointer_cast<IRenderable>(std::move(geometry));
}