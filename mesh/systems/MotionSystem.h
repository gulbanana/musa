#pragma once
#include <core/framework.h>
#include <core/GameState.h>

//provides "realistic" physical motion, no game-specific logic
class MotionSystem : public Identified<MotionSystem, ISystem, EntityManagingSystemBase>
{
	GameState* _state;
	seconds elapsedTime;

	std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;

	void on_frame_start() override;
	void on_frame_entity(std::shared_ptr<IEntity> entity) override;

public:
	MotionSystem(GameState* state);
};

