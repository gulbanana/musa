#include <engine/core.h>
#include "PresetArchetype.h"
using namespace std;

PresetArchetype::~PresetArchetype()
{
}

vector<IComponent*> PresetArchetype::components()
{
	vector<IComponent*> pointers;

	for (auto& component : _components)
	{
		pointers.push_back(component.get());
	}

	return pointers;
}