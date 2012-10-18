#include <engine/core.h>
#include <algorithm>
#include <numeric>
#include "FVMesh.h"
using namespace std;
using namespace glm;

FVMesh::FVMesh(unsigned sides, std::vector<Group>&& groups, std::vector<point>&& vertices) : 
		sides(sides), groups(groups), vertices(vertices), uv_map(), normal_map(), _bounds_cache(calc_bounds()), wireframe(false)
{
	validate_mesh();
}

FVMesh::FVMesh(unsigned sides, std::vector<Group>&& groups, std::vector<point>&& vertices, std::vector<vec2>&& uvs) :
		sides(sides), groups(groups), vertices(vertices), uv_map(uvs), normal_map(), _bounds_cache(calc_bounds()), wireframe(false)
{
	validate_mesh();
}

FVMesh::FVMesh(unsigned sides, std::vector<Group>&& groups, std::vector<point>&& vertices, std::vector<vec3>&& normals) :
		sides(sides), groups(groups), vertices(vertices), uv_map(), normal_map(normals), _bounds_cache(calc_bounds()), wireframe(false)
{
	validate_mesh();
}

FVMesh::FVMesh(unsigned sides, std::vector<Group>&& groups, std::vector<point>&& vertices, std::vector<vec2>&& uvs, std::vector<vec3>&& normals) :
		sides(sides), groups(groups), vertices(vertices), uv_map(uvs), normal_map(normals), _bounds_cache(calc_bounds()), wireframe(false)
{
	validate_mesh();
}

FVMesh::FVMesh(unsigned sides, IMaterial* brush, std::vector<Face>&& faces, std::vector<point>&& vertices) : 
		sides(sides), groups(), vertices(vertices), uv_map(), normal_map(), _bounds_cache(calc_bounds()), wireframe(false)
{
	groups.emplace_back(brush, std::forward<std::vector<Face>>(faces));
	validate_mesh();
}

void FVMesh::accept(IRenderer* renderer) const 
{ 
	renderer->draw(this); 
}

box6 FVMesh::bounds() const 
{ 
	return _bounds_cache; 
}

size_t FVMesh::polygons() const 
{
	return accumulate(groups.begin(), groups.end(), (size_t)0, [](size_t left, Group right){
		return left + right.faces.size();
	});
}

box6 FVMesh::calc_bounds()
{
	coord minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = maxX = maxY = maxZ = 0.0;

	for (auto v : vertices)
	{
		minX = std::min(v.x, minX);
		minY = std::min(v.y, minY);
		minZ = std::min(v.z, minZ);
		maxX = std::max(v.x, maxX);
		maxY = std::max(v.y, maxY);
		maxZ = std::max(v.z, maxZ);
	}
	
	return box6(minX, minY, minZ, maxX, maxY, maxZ);
}

void FVMesh::validate_mesh()
{
	if (sides != 3 && sides != 4)
		throw runtime_error("FVMesh: not composed of triangles or quads");

	has_uv = uv_map.size() != 0;
	has_normal = normal_map.size() != 0;

	for (auto& group : groups)
	{
		for (auto& face : group.faces)
		{
			if (face.vertex_indices.size() != sides)
				throw runtime_error("FVMesh: missing vertex indices for face");
			for (auto index : face.vertex_indices)
				if (index >= vertices.size())
					throw runtime_error("FVMesh: vertex index out of bounds");

			if (has_uv)
			{
				if (face.uv_indices.size() != sides)
					throw runtime_error("FVMesh: missing UV indices for face");
				for (auto index : face.uv_indices)
					if (index >= uv_map.size())
						throw runtime_error("FVMesh: UV index out of bounds");
			}

			if (has_normal)
			{
				if (face.normal_indices.size() != sides)
					throw runtime_error("FVMesh: missing normal indices for face");
								for (auto index : face.normal_indices)
					if (index >= normal_map.size())
						throw runtime_error("FVMesh: normal index out of bounds");
			}
		}
	}
}