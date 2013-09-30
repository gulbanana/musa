#include <tile/stdafx.h>
#include <tile/components.h>
#include <core/misc.h>
#include "Character.h"
using namespace std;

Character::Character(char c)
{
    _components.emplace_back(make_unique<CTransform>(0,0,0));
    _components.emplace_back(make_unique<CVelocity>(0,0));
	_components.emplace_back(make_unique<CDraw>(tile(c, colour::WHITE)));
}
