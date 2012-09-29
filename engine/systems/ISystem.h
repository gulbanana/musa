#pragma once
#include <memory>
#include <vector>
#include <string>
#include <typeinfo>
#include "../entities/IEntity.h"

class ISystem
{
	IDENTIFIABLE
	(
		Control,
		Collision,
		Input,
		Display,
		Motion,
		Physics,
		Render,
		UI
	);

private:
	virtual void on_frame() {}
	virtual void on_entity(std::shared_ptr<IEntity> entity) {}
	virtual void on_post_frame() {}

protected:
	std::vector<std::weak_ptr<IEntity>> entities;

public:
	virtual ~ISystem() {}
	virtual std::vector<IComponent::ID> required_components() { return std::vector<IComponent::ID>(); }
	virtual void add_entity(std::weak_ptr<IEntity> new_entity);
	
	void frame();
};

