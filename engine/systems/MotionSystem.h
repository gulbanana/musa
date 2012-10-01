#pragma once
#include <engine/core.h>
#include <engine/GameState.h>

//provides "realistic" physical motion, no game-specific logic
class MotionSystem : public ISystem
{
	std::shared_ptr<GameState> state;
	float elapsedTime;
	float levelWidth;
	float levelHeight;

public:
	MotionSystem(std::shared_ptr<GameState> state, int boundsX, int boundsY);

	std::vector<IComponent::ID> required_components() override;
	void on_frame() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;
};

