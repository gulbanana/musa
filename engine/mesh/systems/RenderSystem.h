#pragma once
#include <engine/mesh/geometry.h>
#include "render/scene.h"
#include "ThreadedSystemBase.h"

class RenderSystem final : public Identified<ISystem,SYS::Render,ThreadedSystemBase>, public IGraphWalker
{
	std::shared_ptr<IRenderer> _renderer;
	SceneGraph _scene;

	void add_entity(std::weak_ptr<IEntity> entity) override;
	void on_wake() override;
	bool on_event(SDL_Event& event) override;

public:
	RenderSystem(std::shared_ptr<IRenderer>);

	virtual std::vector<ISystem::ID> required_systems() const override;

	void visit(RootNode*) override;
	void visit(BranchNode*) override;
	void visit(LeafNode*) override;
};

