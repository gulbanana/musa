#include <mesh/stdafx.h>
#include <mesh/components.h>
#include "../MotionSystem.h"
#include <iterator>
#include <SDL_opengl.h>
#include "RenderSystem.h"
using namespace std;

vector<ISystem::ID> RenderSystem::required_systems() const 
{
	return require<MotionSystem>();
}

RenderSystem::RenderSystem(shared_ptr<IRenderer> r) : _renderer(r) {}

void RenderSystem::on_entity(weak_ptr<IEntity> new_entity)
{
	auto owned = new_entity.lock();

	if (owned->has_component<CRenderable>())
	{
		auto renderNode = owned->get_component<CRenderable>();
		if (renderNode->geometry->is_camera())
			_scene.add_branch(owned);
		else
			_scene.add_leaf(owned);
	}
}

bool RenderSystem::on_event(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_WINDOWEVENT:
        {
            switch (event.window.event)
            {
                //externally-initiated resize
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                    _renderer->set_viewport(event.window.data1, event.window.data2);
                    break;
                }
            }
            break;
        }

    }
	
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

	auto renderable = node->entity->get_component<CRenderable>();
	renderable->geometry->accept_enter(_renderer.get());

	for (auto& child : node->children)
		child->accept(this);

	renderable->geometry->accept_leave(_renderer.get());
}

void RenderSystem::visit(LeafNode* node)
{
	auto matrix = node->entity->get_component<CTransform>();
	_renderer->set_transform(matrix->translate, matrix->rotate, matrix->scale);

	auto renderNode = node->entity->get_component<CRenderable>();
	renderNode->geometry->accept_enter(_renderer.get());
	renderNode->geometry->accept_leave(_renderer.get());
}