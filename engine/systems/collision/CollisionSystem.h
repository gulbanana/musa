#pragma once
#include <engine/core.h>
#include "ICollisionDetector.h"

class CollisionSystem : public Identified<ISystem,SYS::Collision>
{
	//TODO: inject these?
	std::vector<std::unique_ptr<ICollisionDetector>> detectors;
	std::vector<std::weak_ptr<IEntity>> targets;

	void on_frame() override;
	void on_entity(std::shared_ptr<IEntity> entity) override;

public:
	CollisionSystem();

	std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const  override;

	void add_entity(std::weak_ptr<IEntity> entity) override;
};

