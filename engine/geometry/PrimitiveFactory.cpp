#include <memory>
#include <engine/misc.h>
#include "PrimitiveFactory.h"
#include "FVMesh.h"
using namespace std;

PrimitiveFactory::PrimitiveFactory(shared_ptr<IMaterial> brush) : _brush(brush) {}

unique_ptr<IRenderable> PrimitiveFactory::create_cube(coord radius)
{
	return create_prism(Box6<coord>(-radius, -radius, -radius, radius, radius, radius));
}

unique_ptr<IRenderable> PrimitiveFactory::create_prism(Box6<coord> bounds)
{
	auto vertices = vector<Vec3<coord>>();
	vertices.emplace_back(bounds.left(), bounds.bottom(), bounds.back());
	vertices.emplace_back(bounds.right(), bounds.bottom(), bounds.back());
	vertices.emplace_back(bounds.right(), bounds.top(), bounds.back());
	vertices.emplace_back(bounds.left(), bounds.top(), bounds.back());
	vertices.emplace_back(bounds.left(), bounds.bottom(), bounds.front());
	vertices.emplace_back(bounds.right(), bounds.bottom(), bounds.front());
	vertices.emplace_back(bounds.right(), bounds.top(), bounds.front());
	vertices.emplace_back(bounds.left(), bounds.top(), bounds.front());

	auto quads = vector<FVMesh::Face>();
	quads.emplace_back(0,4,7,3);	//left
	quads.emplace_back(0,1,5,4);	//bottom
	quads.emplace_back(0,1,2,3);	//back
	quads.emplace_back(1,5,6,2);	//right
	quads.emplace_back(3,2,6,7);	//top
	quads.emplace_back(4,5,6,7);	//front

	return make_unique<FVMesh>(4, _brush, std::move(quads), std::move(vertices));
}

unique_ptr<IRenderable> PrimitiveFactory::create_sphere(coord radius)
{
	//generate initial icosahedron
	auto t = (coord)((sqrt(5.0) + 1.0) / 2.0) * radius;

	auto vertices = vector<Vec3<coord>>();
	vertices.emplace_back(-radius, t, (coord)0);
	vertices.emplace_back(radius, t, (coord)0);
	vertices.emplace_back(-radius, -t, (coord)0);
	vertices.emplace_back(radius, -t, (coord)0);

	vertices.emplace_back((coord)0, -radius, t);
	vertices.emplace_back((coord)0, radius, t);
	vertices.emplace_back((coord)0, -radius, -t);
	vertices.emplace_back((coord)0, radius, -t);

	vertices.emplace_back(t, (coord)0, -radius);
	vertices.emplace_back(t, (coord)0, radius);
	vertices.emplace_back(-t, (coord)0, -radius);
	vertices.emplace_back(-t, (coord)0, radius);

	auto quads = vector<FVMesh::Face>();
	quads.emplace_back(0,11,5);
	quads.emplace_back(0,5,1);
	quads.emplace_back(0,1,7);
	quads.emplace_back(0,7,10);
	quads.emplace_back(0,10,11);

	quads.emplace_back(1,5,9);
	quads.emplace_back(5,11,4);
	quads.emplace_back(11,10,2);
	quads.emplace_back(10,7,6);
	quads.emplace_back(7,1,8);

	quads.emplace_back(3,9,4);
	quads.emplace_back(3,4,2);
	quads.emplace_back(3,2,6);
	quads.emplace_back(3,6,8);
	quads.emplace_back(3,8,9);

	quads.emplace_back(4,9,5);
	quads.emplace_back(2,4,11);
	quads.emplace_back(6,2,10);
	quads.emplace_back(8,6,7);
	quads.emplace_back(9,8,1);

	return make_unique<FVMesh>(3, _brush, std::move(quads), std::move(vertices));
}