#pragma once
#include <memory>
#include <map>
#include "../components/IComponent.h"

//	IEntity contract:
//	component pointers remain valid until destruction, so holding ownership of the entity means you can use a pointer acquired earlier
class IEntity
{
protected:
	IEntity() {}

	IDENTIFIABLE_COLLECTION(IComponent, component, components);
};

