#include <array>
#include <iterator>
#include <SDL_opengl.h>
#include <engine/components.h>
#include "RenderSystem.h"
using namespace std;

vector<CMP> RenderSystem::required_components() const 
{
	array<CMP,2> compTypes = {CMP::Position, CMP::Mesh};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<SYS> RenderSystem::required_systems() const 
{
	array<SYS,2> sysTypes = {SYS::Motion, SYS::Logic};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

RenderSystem::RenderSystem(shared_ptr<IRenderer> r) : _renderer(r) {}

bool RenderSystem::on_event(SDL_Event& event)
{
	if (event.type == SDL_VIDEORESIZE)
		_renderer->resize(event.resize.w, event.resize.h);
	
	return false;
}

void RenderSystem::pre_frame()
{
	_renderer->begin_frame();
}

void RenderSystem::post_frame()
{
	_renderer->end_frame();
}

void RenderSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition>();
	auto mesh = entity->get_component<CMesh>();
	
	mesh->geometry->accept(_renderer.get(), position->location, position->orientation);
}