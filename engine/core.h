//precompiled header file
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

//internal
#include "platform.h"       //let's hope this doesn't change too often
#include "core/misc.h"
#include "core/typedefs.h"

//mathematical
#include "core/rect4.h"
#include "core/box6.h"

//utility
#include "core/constants.h"
#include "core/to_string.h"

//architectural
#include "core/Identified.h"
#include "core/IComponent.h"

#include "core/IEntity.h"
#include "core/IArchetype.h"
#include "core/IEntityFactory.h"
#include "core/AutonomousEntity.h"
#include "core/AutonomousEntityFactory.h"
#include "core/ManagedEntity.h"
#include "core/ManagedEntityFactory.h"

#include "core/ISystem.h"