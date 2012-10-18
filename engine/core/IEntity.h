#pragma once
#include <map>
#include "IComponent.h"

//	IEntity contract:
//	component pointers remain valid until destruction, so holding ownership of the entity means you can use a pointer acquired earlier
class IEntity
{
public:
	virtual ~IEntity() = 0;
protected:
	IDENTIFIABLE_COLLECTION(IComponent, component, components);
};

