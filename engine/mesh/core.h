#pragma once

//STL
#define _USE_MATH_DEFINES
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>

//core architecture layer 1
#include <engine/framework/time.h>
#include <engine/framework/IPlatform.h>
#include <engine/framework/Identifiable.h>
#include <engine/framework/IComponent.h>
//layer 2
#include <engine/framework/IEntity.h>
#include <engine/framework/IEntityFactory.h>
#include <engine/framework/IArchetype.h>
#include <engine/framework/ISystem.h>
//layer 3
#include <engine/framework/AutonomousEntity.h>
#include <engine/framework/AutonomousEntityFactory.h>
#include <engine/framework/ManagedEntity.h>
#include <engine/framework/ManagedEntityFactory.h>

//openGL Maths Library
#define GLM_PRECISION_MEDIUMP_FLOAT
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

//mesh-specific types
#include "core/misc.h"
#include "core/typedefs.h"
#include "core/rect4.h"
#include "core/box6.h"
#include "core/constants.h"
#include "core/to_string.h"


