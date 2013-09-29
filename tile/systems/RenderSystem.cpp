#include <tile/stdafx.h>
#include "RenderSystem.h"
using namespace std;

vector<ISystem::ID> RenderSystem::required_systems() const
{
	return require();
}

RenderSystem::RenderSystem(void)
{
}

RenderSystem::~RenderSystem(void)
{
}

void RenderSystem::on_wake()
{
}