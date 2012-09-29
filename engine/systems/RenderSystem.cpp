#include <array>
#include <iterator>
#include <typeinfo>
#include <SDL_opengl.h>
#include "../components.h"
#include "RenderSystem.h"
using namespace std;

vector<IComponent::ID> RenderSystem::required_components()
{
	array<IComponent::ID,2> compTypes = {IComponent::ID::Position2D, IComponent::ID::Geometry2D};
	return vector<IComponent::ID>(compTypes.begin(), compTypes.end());
}

RenderSystem::RenderSystem()
{
	//glinit
}

RenderSystem::~RenderSystem()
{
	//gldestroy
}

void RenderSystem::on_frame()
{
	//gl per frame
}

void RenderSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition2D>();
	auto geometry = entity->get_component<CGeometry2D>();


	//glmatrix stuff based on position

	for (auto& poly : geometry->polys)
	{
		//color stuff?

		poly->draw();
	}

	if (entity->has_component<CLabel>())
	{
		auto label = entity->get_component<CLabel>();
		//gltext
	}
}