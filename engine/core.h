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

//internal types
#include "core/misc.h"
#include "core/typedefs.h"
#include "core/rect4.h"
#include "core/box6.h"
#include "core/constants.h"
#include "core/to_string.h"

//core architecture layer 1
#include "core/IPlatform.h"
#include "core/Identified.h"
#include "core/IComponent.h"
//layer 2
#include "core/IEntity.h"
#include "core/IEntityFactory.h"
#include "core/IArchetype.h"
#include "core/ISystem.h"
//layer 3
#include "core/AutonomousEntity.h"
#include "core/AutonomousEntityFactory.h"
#include "core/ManagedEntity.h"
#include "core/ManagedEntityFactory.h"
