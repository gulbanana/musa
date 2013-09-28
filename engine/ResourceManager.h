#pragma once
#include <engine/mesh/geometry.h>

enum class Primitive
{
	Sphere,
	Cube,
	Prism
};

class ResourceManagerImpl;
class ResourceManager
{
	ResourceManagerImpl* _pimpl;

public:
	ResourceManager();
	~ResourceManager();

	IMaterial* load_brush(glm::vec4);
	IRenderable* load_primitive(SolidColourBrush*, Primitive, void*);
	IRenderable* load_model(IMaterial*);
};

