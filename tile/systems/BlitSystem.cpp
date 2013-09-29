#include <tile/stdafx.h>
#include "BlitSystem.h"
using namespace std;

vector<ISystem::ID> BlitSystem::required_systems() const
{
	return require();
}

BlitSystem::BlitSystem(void)
{
}

BlitSystem::~BlitSystem(void)
{
}

void BlitSystem::on_wake()
{
}