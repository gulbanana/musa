#pragma once
#include <core/GameState.h>
#include <core/systems/EntityManagingSystemBase.h>

//provides "realistic" physical motion, no game-specific logic
class MotionSystem : public Identified<ISystem,SYS::Motion,EntityManagingSystemBase>
{
	std::shared_ptr<GameState> _state;
	seconds elapsedTime;

	std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;

	void on_frame_start() override;
	void on_frame_entity(std::shared_ptr<IEntity> entity) override;

public:
	MotionSystem(std::shared_ptr<GameState> state);
};

