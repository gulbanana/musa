#include <algorithm>
#include "FVMesh.h"
using namespace std;

Box6<coord> FVMesh::calc_bounds()
{
	coord minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = maxX = maxY = maxZ = 0.0;

	for (auto v : vertices)
	{
		minX = min(v.x, minX);
		minY = min(v.y, minY);
		minZ = min(v.z, minZ);
		maxX = max(v.x, maxX);
		maxY = max(v.y, maxY);
		maxZ = max(v.z, maxZ);
	}
	
	return Box6<coord>(minX, minY, minZ, maxX, maxY, maxZ);
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