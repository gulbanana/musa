#include <memory>
#include <map>
#include <engine/misc.h>
#include "PrimitiveFactory.h"
#include "FVMesh.h"
using namespace std;


unique_ptr<IRenderable> PrimitiveFactory::create_cube(IMaterial* brush, coord radius)
{
	return create_prism(brush, Box6<coord>(-radius, -radius, -radius, radius, radius, radius));
}

unique_ptr<IRenderable> PrimitiveFactory::create_prism(IMaterial* brush, Box6<coord> bounds)
{
	vector<Vec3<coord>> vertices;
	vertices.emplace_back(bounds.left(), bounds.bottom(), bounds.back());
	vertices.emplace_back(bounds.right(), bounds.bottom(), bounds.back());
	vertices.emplace_back(bounds.right(), bounds.top(), bounds.back());
	vertices.emplace_back(bounds.left(), bounds.top(), bounds.back());
	vertices.emplace_back(bounds.left(), bounds.bottom(), bounds.front());
	vertices.emplace_back(bounds.right(), bounds.bottom(), bounds.front());
	vertices.emplace_back(bounds.right(), bounds.top(), bounds.front());
	vertices.emplace_back(bounds.left(), bounds.top(), bounds.front());

	vector<FVMesh::Face> quads;
	quads.emplace_back(0,4,7,3);	//left
	quads.emplace_back(0,1,5,4);	//bottom
	quads.emplace_back(0,1,2,3);	//back
	quads.emplace_back(1,5,6,2);	//right
	quads.emplace_back(3,2,6,7);	//top
	quads.emplace_back(4,5,6,7);	//front

	return make_unique<FVMesh>(4, brush, std::move(quads), std::move(vertices));
}

unique_ptr<IRenderable> PrimitiveFactory::create_sphere(IMaterial* brush, coord radius, int refinements)
{
	//generate initial icosahedron
	auto t = (coord)((1.0 + sqrt(5.0)) / 2.0);

	vector<Vec3<coord>> vertices;
	vertices.reserve(12 * (unsigned long)pow(4, refinements));

	auto addvertex = [&](Vec3<coord> v)
	{
		v.normalize();
		v *= radius;

		int i, vix = -1;
		for (i = 0; i < vertices.size(); i++)
		{
			if (vertices[i] == v)
			{
				vix = i;
				break;
			}
		}

		if (vix == -1)
		{
			vertices.emplace_back(v);
			vix = i;
		}
		return vix;
	};

	addvertex(Vec3<coord>((coord)-1, t, (coord)0));
	addvertex(Vec3<coord>((coord)1, t, (coord)0));
	addvertex(Vec3<coord>((coord)-1, -t, (coord)0));
	addvertex(Vec3<coord>((coord)1, -t, (coord)0));

	addvertex(Vec3<coord>((coord)0, (coord)-1, t));
	addvertex(Vec3<coord>((coord)0, (coord)1, t));
	addvertex(Vec3<coord>((coord)0, (coord)-1, -t));
	addvertex(Vec3<coord>((coord)0, (coord)1, -t));

	addvertex(Vec3<coord>(t, (coord)0, (coord)-1));
	addvertex(Vec3<coord>(t, (coord)0, (coord)1));
	addvertex(Vec3<coord>(-t, (coord)0, (coord)-1));
	addvertex(Vec3<coord>(-t, (coord)0, (coord)1));

	vector<FVMesh::Face> triangles;
	triangles.reserve(20 * (unsigned long)pow(4, refinements));
	triangles.emplace_back(0,11,5);
	triangles.emplace_back(0,5,1);
	triangles.emplace_back(0,1,7);
	triangles.emplace_back(0,7,10);
	triangles.emplace_back(0,10,11);

	triangles.emplace_back(1,5,9);
	triangles.emplace_back(5,11,4);
	triangles.emplace_back(11,10,2);
	triangles.emplace_back(10,7,6);
	triangles.emplace_back(7,1,8);

	triangles.emplace_back(3,9,4);
	triangles.emplace_back(3,4,2);
	triangles.emplace_back(3,2,6);
	triangles.emplace_back(3,6,8);
	triangles.emplace_back(3,8,9);

	triangles.emplace_back(4,9,5);
	triangles.emplace_back(2,4,11);
	triangles.emplace_back(6,2,10);
	triangles.emplace_back(8,6,7);
	triangles.emplace_back(9,8,1);

	//refine the icosahedron several times by splitting each of its triangles into 4 triangles
	map<Vec3<coord>*, int> vcache;
	for (int i = 0; i < refinements; i++)
	{
		vector<FVMesh::Face> newFaces;
		for (auto face : triangles)
		{
			auto makevertex = [&](int vi1, int vi2)
			{
				return Vec3<coord>::midpoint(vertices[face.vertex_indices[vi1]], vertices[face.vertex_indices[vi2]]);
			};

			int aix = addvertex(makevertex(0,1));
			int bix = addvertex(makevertex(1,2));
			int cix = addvertex(makevertex(2,0));

			newFaces.emplace_back(face.vertex_indices[0], aix, cix);
			newFaces.emplace_back(face.vertex_indices[1], bix, aix);
			newFaces.emplace_back(face.vertex_indices[2], cix, bix);
			newFaces.emplace_back(aix, bix, cix);
		}
		triangles = newFaces;
	}

	return make_unique<FVMesh>(3, brush, std::move(triangles), std::move(vertices));
}