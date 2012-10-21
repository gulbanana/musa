#include <engine/core.h>
#include <engine/components.h>
#include <iterator>
#include <SDL_opengl.h>
#include "RenderSystem.h"
using namespace std;

vector<SYS> RenderSystem::required_systems() const 
{
	return require(SYS::Motion, SYS::Logic);
}

RenderSystem::RenderSystem(shared_ptr<IRenderer> r) : _renderer(r) {}

void RenderSystem::add_entity(weak_ptr<IEntity> new_entity)
{
	auto owned = new_entity.lock();

	if (owned->has_component<CCamera>())
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
	auto matrix = node->entity->get_component<CTransform>();
	_renderer->set_transform(matrix->translate, matrix->rotate, matrix->scale);

	auto renderable = node->entity->get_component<CCamera>();
	renderable->view->accept_enter(_renderer.get());

	for (auto& child : node->children)
		child->accept(this);

	renderable->view->accept_leave(_renderer.get());
}

void RenderSystem::visit(LeafNode* node)
{
	auto matrix = node->entity->get_component<CTransform>();
	_renderer->set_transform(matrix->translate, matrix->rotate, matrix->scale);

	auto renderNode = node->entity->get_component<CModel>();
	renderNode->geometry->accept_enter(_renderer.get());
	renderNode->geometry->accept_leave(_renderer.get());
}