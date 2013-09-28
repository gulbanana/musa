#include <core/stdafx.h>
#include "ArchetypeBase.h"
using namespace std;

ArchetypeBase::~ArchetypeBase()
{
}

vector<IComponent*> ArchetypeBase::components()
{
	vector<IComponent*> pointers;

	for (auto& component : _components)
	{
		pointers.push_back(component.get());
	}

	return pointers;
}