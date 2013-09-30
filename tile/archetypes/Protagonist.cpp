#include <tile/stdafx.h>
#include <tile/components.h>
#include <core/misc.h>
#include "Protagonist.h"
using namespace std;

Protagonist::Protagonist() : Character('@')
{
    _components.emplace_back(make_unique<CKBMInput>());
    _components.emplace_back(make_unique<CPadInput>());
}

Protagonist::~Protagonist()
{
}
