#pragma once
#include <array>
#include "IModel.h"
#include "IMaterial.h"

//"Face-Vertex" mesh- small storage, fast rendering, no dynamic edits. quad or tri faces.
struct FVMesh : public IModel
{
	struct Face
	{
		std::vector<unsigned> vertex_indices;
		std::vector<unsigned> uv_indices;
		std::vector<unsigned> normal_indices;

		Face(std::vector<unsigned>&& vertex_indices) : vertex_indices(vertex_indices) {}
		Face(unsigned a, unsigned b, unsigned c) : vertex_indices()
		{
			vertex_indices.push_back(a);
			vertex_indices.push_back(b);
			vertex_indices.push_back(c);
		}
		Face(unsigned a, unsigned b, unsigned c, unsigned d) : vertex_indices()
		{
			vertex_indices.push_back(a);
			vertex_indices.push_back(b);
			vertex_indices.push_back(c);
			vertex_indices.push_back(d);
		}
	};

	struct Group
	{
		IMaterial* brush;
		std::vector<Face> faces;

		Group(IMaterial* brush, std::vector<Face>&& faces) : brush(brush), faces(move(faces)) {}
	};

	std::vector<Group> groups;
	std::vector<Vec3<coord>> vertices;
	std::vector<Vec2<coord>> uv_map;
	std::vector<Vec3<coord>> normal_map;

	unsigned sides;
	bool has_uv;
	bool has_normal;
	bool wireframe;

	FVMesh(unsigned sides, std::vector<Group>&& groups, std::vector<Vec3<coord>>&& vertices);
	FVMesh(unsigned sides, IMaterial* brush, std::vector<Face>&& faces, std::vector<Vec3<coord>>&& vertices);
	FVMesh(unsigned sides, std::vector<Group>&& groups, std::vector<Vec3<coord>>&& vertices, std::vector<Vec2<coord>>&& uvs);
	FVMesh(unsigned sides, std::vector<Group>&& groups, std::vector<Vec3<coord>>&& vertices, std::vector<Vec3<coord>>&& normals);
	FVMesh(unsigned sides, std::vector<Group>&& groups, std::vector<Vec3<coord>>&& vertices, std::vector<Vec2<coord>>&& uvs, std::vector<Vec3<coord>>&& normals);

	void accept(IRenderer* renderer) const override; 
	Box6<coord> bounds() const override; 
	size_t polygons() const override; 
	
private:
	Box6<coord> _bounds_cache;
	Box6<coord> calc_bounds();
	void validate_mesh();
};

