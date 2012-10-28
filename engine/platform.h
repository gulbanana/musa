#pragma once

#ifdef _MSC_VER
	#include "windows/msvc.h"
#endif

#ifdef ___SOME_mac_thing__
#endif

namespace debug
{
    void print(std::string output);
}