#include <engine/core.h>
#include <stdexcept>
#include "ResourceManager.h"
using namespace std;

#pragma region pimpl
class ResourceManagerImpl
{
	vector<IMaterial*> _deletionPool;
	map<string, unique_ptr<IModel>> _meshCache;

public:
	ResourceManagerImpl();
	~ResourceManagerImpl();

	IMaterial* load_brush(Colour4F);
	IModel* load_primitive(SolidColourBrush*, Primitive, void*);
	IModel* load_model(IMaterial*);
};
ResourceManager::ResourceManager() : _pimpl(new ResourceManagerImpl()) {}
ResourceManager::~ResourceManager() { delete _pimpl; }
IMaterial* ResourceManager::load_brush(Colour4F c) { return _pimpl->load_brush(c); }
IModel* ResourceManager::load_primitive(SolidColourBrush* m, Primitive p, void* arg) { return _pimpl->load_primitive(m, p, arg); }
IModel* ResourceManager::load_model(IMaterial* m) { return _pimpl->load_model(m); }
#pragma endregion


ResourceManagerImpl::ResourceManagerImpl() : _deletionPool(), _meshCache()
{
}

ResourceManagerImpl::~ResourceManagerImpl()
{
	for (auto pointer : _deletionPool)
		delete pointer;
}


IMaterial* ResourceManagerImpl::load_brush(Colour4F c)
{
	auto material = new SolidColourBrush(c);
	_deletionPool.push_back(material);
	return material;
}

IModel* ResourceManagerImpl::load_primitive(SolidColourBrush* brush, Primitive shape, void* arg)
{
	string hash;	//this works but sucks
	coord radius;
	Box6<coord>* bounds;

	switch(shape)
	{
	case Primitive::Sphere:
		radius = *(coord*)arg;
		hash = to_string(brush->colour) + "S" + to_string(radius);

		if (_meshCache.find(hash) == _meshCache.end())
			_meshCache[hash] = PrimitiveFactory::create_sphere(brush, radius);
		break;

	case Primitive::Cube:
		radius = *(coord*)arg;
		hash = to_string(brush->colour) + "C" + to_string(radius + 10000);

		if (_meshCache.find(hash) == _meshCache.end())
			_meshCache[hash] = PrimitiveFactory::create_cube(brush, radius);
		break;

	case Primitive::Prism:
		bounds = (Box6<coord>*)arg;
		hash = to_string(brush->colour) + "R" + to_string(*bounds);

		if (_meshCache.find(hash) == _meshCache.end())
			_meshCache[hash] = PrimitiveFactory::create_prism(brush, *bounds);
		break;

	default:
		throw runtime_error("Incorrect primitive type specified.");
	}

	return _meshCache[hash].get();
}

IModel* ResourceManagerImpl::load_model(IMaterial*)
{
	return nullptr;
}