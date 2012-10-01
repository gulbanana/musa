#include <array>
#include <iterator>
#include <typeinfo>
#include <engine/components.h>
#include "RenderSystem.h"
#include <SDL_opengl.h>
using namespace std;

vector<CID> RenderSystem::required_components()
{
	array<CID,3> compTypes = {CID::Position, CID::Brush, CID::Mesh};
	return vector<CID>(compTypes.begin(), compTypes.end());
}

RenderSystem::RenderSystem(unique_ptr<IRenderer> r) : _renderer(std::move(r)) {}

bool RenderSystem::on_event(SDL_Event& event)
{
	//gl reset size or something
	return false;
}

void RenderSystem::on_frame()
{
	_renderer->begin_frame();
}

void RenderSystem::on_post_frame()
{
	_renderer->end_frame();
}

void RenderSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition>();
	auto brush = entity->get_component<CBrush>();
	auto mesh = entity->get_component<CMesh>();
	
	mesh->geometry->accept(_renderer.get(), brush->color, position->location, position->orientation);
}