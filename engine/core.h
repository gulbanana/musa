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
//#include "core/coord.h"
#include "core/typedefs.h"
#include "core/rect4.h"
#include "core/box6.h"
#include "core/constants.h"
#include "core/to_string.h"

//core architecture layer 1
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
