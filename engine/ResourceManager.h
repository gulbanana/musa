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

	IMaterial* load_brush(Colour4F);
	IModel* load_primitive(SolidColourBrush*, Primitive, void*);
	IModel* load_model(IMaterial*);
};

