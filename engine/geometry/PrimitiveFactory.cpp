#include <memory>
#include <engine/misc.h>
#include "PrimitiveFactory.h"
#include "VVMesh.h"
using namespace std;

unique_ptr<IRenderable> PrimitiveFactory::create_cube(coord radius)
{
	return create_prism(Box6<coord>(-radius, -radius, -radius, radius, radius, radius));
}

unique_ptr<IRenderable> PrimitiveFactory::create_prism(Box6<coord> bounds)
{
	auto vertices = vector<VVMesh::Vertex>();

	vertices.emplace_back(bounds.left(), bounds.bottom(), bounds.back());
	vertices[0].adjacent.push_back(1);
	vertices[0].adjacent.push_back(3);
	vertices[0].adjacent.push_back(4);

	vertices.emplace_back(bounds.right(), bounds.bottom(), bounds.back());
	vertices[1].adjacent.push_back(0);
	vertices[1].adjacent.push_back(2);
	vertices[1].adjacent.push_back(5);

	vertices.emplace_back(bounds.right(), bounds.top(), bounds.back());
	vertices[2].adjacent.push_back(1);
	vertices[2].adjacent.push_back(3);
	vertices[2].adjacent.push_back(6);

	vertices.emplace_back(bounds.left(), bounds.top(), bounds.back());
	vertices[3].adjacent.push_back(0);
	vertices[3].adjacent.push_back(2);
	vertices[3].adjacent.push_back(7);

	vertices.emplace_back(bounds.left(), bounds.bottom(), bounds.front());
	vertices[4].adjacent.push_back(5);
	vertices[4].adjacent.push_back(7);
	vertices[4].adjacent.push_back(0);

	vertices.emplace_back(bounds.right(), bounds.bottom(), bounds.front());
	vertices[5].adjacent.push_back(4);
	vertices[5].adjacent.push_back(6);
	vertices[5].adjacent.push_back(1);

	vertices.emplace_back(bounds.right(), bounds.top(), bounds.front());
	vertices[4].adjacent.push_back(5);
	vertices[4].adjacent.push_back(7);
	vertices[4].adjacent.push_back(2);

	vertices.emplace_back(bounds.left(), bounds.top(), bounds.front());
	vertices[5].adjacent.push_back(4);
	vertices[5].adjacent.push_back(6);
	vertices[5].adjacent.push_back(3);

	return make_unique<VVMesh>(std::move(vertices));
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