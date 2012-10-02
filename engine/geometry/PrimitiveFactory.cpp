#pragma once
#include <memory>
#include <engine/misc.h>
#include "PrimitiveFactory.h"
#include "VVMesh.h"
using namespace std;

unique_ptr<IRenderable> PrimitiveFactory::create_cube(float radius)
{
	auto vertices = vector<VVMesh::Vertex>();

	vertices.emplace_back(-radius, -radius, -radius);
	vertices[0].adjacent.push_back(1);
	vertices[0].adjacent.push_back(3);
	vertices[0].adjacent.push_back(4);

	vertices.emplace_back(radius, -radius, -radius);
	vertices[1].adjacent.push_back(0);
	vertices[1].adjacent.push_back(2);
	vertices[1].adjacent.push_back(5);

	vertices.emplace_back(radius, radius, -radius);
	vertices[2].adjacent.push_back(1);
	vertices[2].adjacent.push_back(3);
	vertices[2].adjacent.push_back(6);

	vertices.emplace_back(-radius, radius, -radius);
	vertices[3].adjacent.push_back(0);
	vertices[3].adjacent.push_back(2);
	vertices[3].adjacent.push_back(7);

	vertices.emplace_back(-radius, -radius, radius);
	vertices[4].adjacent.push_back(5);
	vertices[4].adjacent.push_back(7);
	vertices[4].adjacent.push_back(0);

	vertices.emplace_back(radius, -radius, radius);
	vertices[5].adjacent.push_back(4);
	vertices[5].adjacent.push_back(6);
	vertices[5].adjacent.push_back(1);

	vertices.emplace_back(radius, radius, radius);
	vertices[4].adjacent.push_back(5);
	vertices[4].adjacent.push_back(7);
	vertices[4].adjacent.push_back(2);

	vertices.emplace_back(-radius, radius, radius);
	vertices[5].adjacent.push_back(4);
	vertices[5].adjacent.push_back(6);
	vertices[5].adjacent.push_back(3);

	return make_unique<VVMesh>(std::move(vertices));
}

unique_ptr<IRenderable> PrimitiveFactory::create_prism(Box6F bounds)
{
	return create_cube(10.f);
}

unique_ptr<IRenderable> PrimitiveFactory::create_sphere(float radius)
{
	return create_cube(radius);
}