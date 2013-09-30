#pragma once
#include <core/framework.h>
#include "ICollisionDetector.h"

class CollisionSystem final : public Identified<CollisionSystem,ISystem,EntityManagingSystemBase>
{
	std::vector<std::unique_ptr<ICollisionDetector>> detectors;	//TODO: inject these?
	std::vector<std::weak_ptr<IEntity>> targets;
	
	std::vector<IComponent::ID> required_components() const override;
	std::vector<ISystem::ID> required_systems() const  override;

	void on_add(std::shared_ptr<IEntity> entity) override;
	void on_frame_start() override;
	void on_frame_entity(std::shared_ptr<IEntity> entity) override;

public:
	CollisionSystem();
};

