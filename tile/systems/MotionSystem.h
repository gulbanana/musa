#pragma once
#include <core/framework.h>
#include <core/GameState.h>

class MotionSystem : public Identified<MotionSystem, ISystem, EntityManagingSystemBase>
{
private:
	GameState* _state;

private:
	std::vector<ISystem::ID> required_systems() const override;
    std::vector<IComponent::ID> required_components() const override;
    void on_frame_entity(std::shared_ptr<IEntity>) override;

public:
	MotionSystem(GameState*);
};

