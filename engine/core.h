#pragma once

//STL
#define _USE_MATH_DEFINES
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>

//openGL Maths Library
#define GLM_PRECISION_MEDIUMP_FLOAT
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

//core geometry model types
#include "core/misc.h"
#include "core/time.h"
#include "core/orientation.h"
#include "core/location.h"
#include "core/colour.h"
#include "core/rect4.h"
#include "core/box6.h"
#include "core/to_string.h"

//ECS architecture layer 1
#include "framework/IPlatform.h"
#include "framework/Identifiable.h"
#include "framework/IComponent.h"
//layer 2
#include "framework/IEntity.h"
#include "framework/IEntityFactory.h"
#include "framework/IArchetype.h"
#include "framework/ISystem.h"
//layer 3
#include "framework/AutonomousEntity.h"
#include "framework/AutonomousEntityFactory.h"
#include "framework/ManagedEntity.h"
#include "framework/ManagedEntityFactory.h"
