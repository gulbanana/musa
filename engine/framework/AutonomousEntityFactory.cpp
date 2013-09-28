#include <engine/core.h>
#include "AutonomousEntityFactory.h"
using namespace std;

unique_ptr<IEntity> AutonomousEntityFactory::create(IArchetype* archetype)
{
	auto entity = new AutonomousEntity();

	if (archetype != nullptr)
	{
		for (auto cmp : archetype->components())
		{
			entity->add_component(cmp->id(), cmp->clone());
		}
	}

	return unique_ptr<IEntity>(entity);
}