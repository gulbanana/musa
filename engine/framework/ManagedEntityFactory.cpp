#include <engine/mesh/core.h>
#include "ManagedEntityFactory.h"
using namespace std;

ManagedEntityFactory::ManagedEntityFactory()
{
	_next = 0;
}

unique_ptr<IEntity> ManagedEntityFactory::create(IArchetype* archetype)
{
	auto id = _next++;
	auto entity = new ManagedEntity(id, this);

	if (archetype != nullptr)
	{
		for (auto cmp : archetype->components())
		{
			add_component(id, cmp->id(), cmp->clone());
		}
	}

	return unique_ptr<IEntity>(entity);
}