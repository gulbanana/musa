#pragma once
#include <engine/core.h>
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

	IMaterial* load_brush(Colour4F);
	IRenderable* load_primitive(IMaterial*, Primitive, void*);
	IRenderable* load_model(IMaterial*);
};

