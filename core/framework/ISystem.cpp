#include <core/stdafx.h>
#include "ISystem.h"

namespace std
{
    string to_string(ISystem* system)
    {
        return system->description();
    }
}