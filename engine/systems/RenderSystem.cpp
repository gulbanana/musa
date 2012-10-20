#include <engine/core.h>
#include <engine/components.h>
#include <iterator>
#include <SDL_opengl.h>
#include "RenderSystem.h"
using namespace std;

vector<SYS> RenderSystem::required_systems() const 
{
	array<SYS,2> sysTypes = {SYS::Motion, SYS::Logic};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

RenderSystem::RenderSystem(shared_ptr<IRenderer> r) : _renderer(r) {}

void RenderSystem::add_entity(weak_ptr<IEntity> new_entity)
{
	auto owned = new_entity.lock();

	if (owned->has_component<CTransform>())
		_scene.add_branch(owned);

	if (owned->has_component<CModel>())
		_scene.add_leaf(owned);
}

bool RenderSystem::on_event(SDL_Event& event)
{
	if (event.type == SDL_VIDEORESIZE)
		_renderer->set_viewport(event.resize.w, event.resize.h);
	
	return false;
}

void RenderSystem::on_wake()
{
	_renderer->begin_frame();
	_scene.node_tree()->accept(this);
	_renderer->end_frame();
}

void RenderSystem::visit(RootNode* node)
{
	for (auto& child : node->children)
		child->accept(this);
}

void RenderSystem::visit(BranchNode* node)
{
	if (node->entity->has_component<CPosition>())
	{
		auto position = node->entity->get_component<CPosition>();
		_renderer->with_position(position->location, position->orientation);
	}

	if (node->entity->has_component<CTransform>())
	{
		auto transformNode = node->entity->get_component<CTransform>();
		transformNode->view->invite(_renderer.get());
	}

	for (auto& child : node->children)
		child->accept(this);

	if (node->entity->has_component<CTransform>())
	{
		auto transformNode = node->entity->get_component<CTransform>();
		transformNode->view->accept(_renderer.get());
	}
}

void RenderSystem::visit(LeafNode* node)
{
	if (node->entity->has_component<CPosition>())
	{
		auto position = node->entity->get_component<CPosition>();
		_renderer->with_position(position->location, position->orientation);
	}

	if (node->entity->has_component<CModel>())
	{
		auto renderNode = node->entity->get_component<CModel>();
		renderNode->geometry->accept(_renderer.get());
	}
}