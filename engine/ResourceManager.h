#pragma once
#include <engine/geometry.h>

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
	IModel* load_primitive(SolidColourBrush*, Primitive, void*);
	IModel* load_model(IMaterial*);
};

