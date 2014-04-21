#pragma once

//ECS architecture layer 1
#include <core/framework/IPlatform.h>
#include <core/framework/Identifiable.h>
#include <core/framework/IComponent.h>
//layer 2 - game objects and logic
#include <core/framework/IEntity.h>
#include <core/framework/IEntityFactory.h>
#include <core/framework/IArchetype.h>
#include <core/framework/ISystem.h>
//layer 3 - factories and concrete
#include <core/framework/ArchetypeBase.h>
#include <core/framework/EntityManagingSystemBase.h>
#include <core/framework/AutonomousEntity.h>
#include <core/framework/AutonomousEntityFactory.h>
#include <core/framework/ManagedEntity.h>
#include <core/framework/ManagedEntityFactory.h>