#include <engine/core.h>
#include <array>
#include <iterator>
#include <SDL_opengl.h>
#include <engine/components.h>
#include "RenderSystem.h"
using namespace std;

vector<CMP> RenderSystem::required_components() const 
{
	array<CMP,1> compTypes = {CMP::Scene};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<SYS> RenderSystem::required_systems() const 
{
	array<SYS,2> sysTypes = {SYS::Motion, SYS::Logic};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

RenderSystem::RenderSystem(shared_ptr<IRenderer> r) : _renderer(r) {}

void RenderSystem::add_entity(weak_ptr<IEntity> new_entity)
{ 
}

void RenderSystem::set_root(shared_ptr<IGraphNode> node)
{ 
	_scene = static_pointer_cast<RootNode>(node); 
}

bool RenderSystem::on_event(SDL_Event& event)
{
	if (event.type == SDL_VIDEORESIZE)
		_renderer->set_viewport(event.resize.w, event.resize.h);
	
	return false;
}

void RenderSystem::on_wake()
{
	auto graph = _scene.lock();

	_renderer->begin_frame();
	graph->accept(this);
	_renderer->end_frame();
}

void RenderSystem::visit(IGraphNode* node)
{
	if (node->_entity->has_component<CPosition>())
	{
		auto position = node->_entity->get_component<CPosition>();
		_renderer->with_position(position->location, position->orientation);
	}
}

void RenderSystem::visit(BranchNode* node)
{
	visit(static_cast<IGraphNode*>(node));

	if (node->_entity->has_component<CTransform>())
	{
		auto transformNode = node->_entity->get_component<CTransform>();
		transformNode->matrix->accept(_renderer.get());
	}

	for (auto child : node->children)
		child->accept(this);

	if (node->_entity->has_component<CTransform>())
	{
		auto transformNode = node->_entity->get_component<CTransform>();
		transformNode->matrix->eject(_renderer.get());
	}
}

void RenderSystem::visit(LeafNode* node)
{
	visit(static_cast<IGraphNode*>(node));

	if (node->_entity->has_component<CMesh>())
	{
		auto renderNode = node->_entity->get_component<CMesh>();
		renderNode->geometry->accept(_renderer.get());
	}
}