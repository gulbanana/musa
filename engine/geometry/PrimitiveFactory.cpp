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
	return create_cube(radius);
		//XXX this is not correct
	/*glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.f, 0.f);
		for (int i = 0; i <= resolution; i++)
			glVertex2f(cos(i * arc) * mesh->radius, sin(i * arc) * mesh->radius);	
	glEnd();*/
}