#pragma once
#include <engine/core.h>
#include <engine/GameState.h>
#include "EntityManagingSystemBase.h"

//provides "realistic" physical motion, no game-specific logic
class MotionSystem : public Identified<ISystem,SYS::Motion,EntityManagingSystemBase>
{
	std::shared_ptr<GameState> state;
	seconds elapsedTime;

	void pre_frame() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;

public:
	MotionSystem(std::shared_ptr<GameState> state);

	std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;
};

